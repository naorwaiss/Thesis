import os
from glob import glob
from setuptools import setup

package_name = 'camera_nav'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='naor',
    maintainer_email='naor@example.com',
    description='Camera navigation package for building 2D costmaps from pointcloud data',
    license='Apache License 2.0',
    entry_points={
        'console_scripts': [],
    },
)

