from setuptools import find_packages
from setuptools import setup

setup(
    name='hamma_bot',
    version='0.0.1',
    packages=find_packages(
        include=('hamma_bot', 'hamma_bot.*')),
)
