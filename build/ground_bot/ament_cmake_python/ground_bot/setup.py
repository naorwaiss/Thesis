from setuptools import find_packages
from setuptools import setup

setup(
    name='ground_bot',
    version='0.0.1',
    packages=find_packages(
        include=('ground_bot', 'ground_bot.*')),
)
