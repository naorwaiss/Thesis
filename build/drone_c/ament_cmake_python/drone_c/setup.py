from setuptools import find_packages
from setuptools import setup

setup(
    name='drone_c',
    version='0.0.1',
    packages=find_packages(
        include=('drone_c', 'drone_c.*')),
)
