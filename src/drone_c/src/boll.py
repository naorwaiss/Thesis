import sys
import numpy as np
from PyQt5.QtWidgets import QApplication, QMainWindow, QOpenGLWidget
from PyQt5.QtCore import Qt
from OpenGL.GL import *
from OpenGL.GLU import gluPerspective
from OpenGL.GLUT import glutBitmapCharacter, GLUT_BITMAP_HELVETICA_18, glutInit
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Quaternion
from threading import Thread


def quaternion_to_rotation_matrix(q):
    q_w, q_x, q_y, q_z = q.w, q.x, q.y, q.z
    R = np.array([[1 - 2 * q_y**2 - 2 * q_z**2, 2 * q_x * q_y - 2 * q_z * q_w, 2 * q_x * q_z + 2 * q_y * q_w],
                  [2 * q_x * q_y + 2 * q_z * q_w, 1 - 2 * q_x**2 - 2 * q_z**2, 2 * q_y * q_z - 2 * q_x * q_w],
                  [2 * q_x * q_z - 2 * q_y * q_w, 2 * q_y * q_z + 2 * q_x * q_w, 1 - 2 * q_x**2 - 2 * q_y**2]])
    return R


class OpenGLWidget(QOpenGLWidget):
    def __init__(self):
        super().__init__()
        self.rotation_matrix = np.eye(3)  # Default rotation matrix
        self.setMinimumSize(800, 600)

    def initializeGL(self):
        print("initializeGL called")
        glutInit()  # Initialize GLUT to use GLUT functions
        glEnable(GL_DEPTH_TEST)
        glClearColor(0.0, 0.0, 0.0, 1.0)  # Black background

    def resizeGL(self, w, h):
        print(f"resizeGL called: width={w}, height={h}")
        if h == 0:  # Prevent divide-by-zero
            h = 1
        glViewport(0, 0, w, h)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()

        # Orthographic projection for isometric view
        scale = 2.0  # Adjust scale for zoom
        aspect_ratio = w / h
        if aspect_ratio >= 1.0:
            glOrtho(-scale * aspect_ratio, scale * aspect_ratio, -scale, scale, -10.0, 10.0)
        else:
            glOrtho(-scale, scale, -scale / aspect_ratio, scale / aspect_ratio, -10.0, 10.0)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def paintGL(self):
        print("paintGL called")
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()

        # Set up the isometric camera view
        glTranslatef(0, 0, -5)  # Move the camera back
        glRotatef(30, 1, 0, 0)  # Tilt down on X-axis
        glRotatef(45, 0, 1, 0)  # Rotate around Y-axis

        # Draw world axes
        self.draw_axes()

        # Draw rotated object axes
        self.draw_object_axes(self.rotation_matrix)

    def draw_axes(self):
        glLineWidth(3.0)  # Make axes lines thicker
        glBegin(GL_LINES)
        # X-axis (red)
        glColor3f(1, 0, 0)
        glVertex3f(0, 0, 0)
        glVertex3f(1, 0, 0)

        # Y-axis (green)
        glColor3f(0, 1, 0)
        glVertex3f(0, 0, 0)
        glVertex3f(0, 1, 0)

        # Z-axis (blue)
        glColor3f(0, 0, 1)
        glVertex3f(0, 0, 0)
        glVertex3f(0, 0, 1)
        glEnd()

        self.draw_axis_labels()

    def draw_object_axes(self, R):
        glLineWidth(3.0)  # Make object axes lines thicker
        axes = np.eye(3)  # Local axes
        transformed_axes = R @ axes

        glBegin(GL_LINES)
        # Transformed X-axis
        glColor3f(1, 0, 0)
        glVertex3f(0, 0, 0)
        glVertex3f(*transformed_axes[:, 0])

        # Transformed Y-axis
        glColor3f(0, 1, 0)
        glVertex3f(0, 0, 0)
        glVertex3f(*transformed_axes[:, 1])

        # Transformed Z-axis
        glColor3f(0, 0, 1)
        glVertex3f(0, 0, 0)
        glVertex3f(*transformed_axes[:, 2])
        glEnd()

        self.draw_object_axis_labels(transformed_axes)

    def draw_axis_labels(self):
        # Render text labels for world axes
        self.render_text(1.1, 0, 0, "X", (1, 0, 0))
        self.render_text(0, 1.1, 0, "Y", (0, 1, 0))
        self.render_text(0, 0, 1.1, "Z", (0, 0, 1))

    def draw_object_axis_labels(self, transformed_axes):
        # Render text labels for object axes
        self.render_text(*transformed_axes[:, 0] * 1.1, "X'", (1, 0, 0))
        self.render_text(*transformed_axes[:, 1] * 1.1, "Y'", (0, 1, 0))
        self.render_text(*transformed_axes[:, 2] * 1.1, "Z'", (0, 0, 1))

    def render_text(self, x, y, z, text, color):
        glColor3f(*color)
        glRasterPos3f(x, y, z)
        for char in text:
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(char))

    def update_rotation(self, R):
        print(f"Updating rotation matrix:\n{R}")
        self.rotation_matrix = R
        self.update()  # Trigger repaint


class QuaternionListener(Node):
    def __init__(self, opengl_widget):
        super().__init__('quaternion_listener')
        self.opengl_widget = opengl_widget
        self.subscription = self.create_subscription(
            Quaternion,
            '/quaternion_data',  # Corrected topic name
            self.listener_callback,
            10
        )
        self.get_logger().info("Quaternion Listener Node Initialized")

    def listener_callback(self, msg):
        print(f"Received quaternion: w={msg.w}, x={msg.x}, y={msg.y}, z={msg.z}")
        R = quaternion_to_rotation_matrix(msg)
        self.opengl_widget.update_rotation(R)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Quaternion Visualization")
        self.opengl_widget = OpenGLWidget()
        self.setCentralWidget(self.opengl_widget)


def main(args=None):
    # Disable shared memory transport
    import os
    os.environ["RMW_TRANSPORT_MODE"] = "udp"

    rclpy.init(args=args)
    app = QApplication(sys.argv)

    main_window = MainWindow()
    main_window.show()

    quaternion_listener = QuaternionListener(main_window.opengl_widget)

    def ros_spin():
        rclpy_executor = rclpy.executors.SingleThreadedExecutor()
        rclpy_executor.add_node(quaternion_listener)
        try:
            rclpy_executor.spin()
        finally:
            quaternion_listener.destroy_node()
            rclpy.shutdown()

    ros_thread = Thread(target=ros_spin, daemon=True)
    ros_thread.start()

    app_exec = app.exec_()
    ros_thread.join()


if __name__ == '__main__':
    main()
