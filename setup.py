#!/usr/bin/env python
#
# Copyright 2013 Bernardo Heynemann <heynemann@gmail.com>
#
import distutils.core
# Importing setuptools adds some features like "setup.py develop", but
# it's optional so swallow the error if it's not there.
try:
    import setuptools
except ImportError:
    pass

kwargs = {
    "install_requires": [
    ],
    "extras_require": {
        'tests': ['nose'],
    }
}

version = "0.1.0"

distutils.core.setup(
    name="grimheaper",
    version=version,
    packages=["grimheaper"],
    author="Bernardo Heynemann",
    author_email="heynemann@gmail.com",
    url="http://heynemann.github.io/grimheaper",
    license="http://opensource.org/licenses/MIT",
    description="Grim Heaper is an implementation of a binary heap in python.",
    long_description="Grim Heaper is an implementation of a binary heap in python.",
    classifiers=[
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: Implementation :: CPython',
        'Programming Language :: Python :: Implementation :: PyPy',
    ],
    **kwargs
)
