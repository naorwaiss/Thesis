from setuptools import find_packages, setup

package_name = 'controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # Include the launch files
        ('share/' + package_name + '/launch', ['launch/joystick_launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='naor',
    maintainer_email='naor-w@apeiro-motion.com',
    description='Package for joystick control with dynamic launch support',
    license='Apache-2.0',
    entry_points={
        'console_scripts': [
        ],
    },
)

