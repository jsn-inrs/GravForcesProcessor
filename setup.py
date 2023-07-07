from setuptools import setup, Extension

# Nom du module SWIG
module_name = '_GravForcesProcessor'

# Extension du module SWIG
extension_mod = Extension(
    module_name,
    sources=['GravForcesProcessorPYTHON_wrap.cxx'],
    libraries=['GravForcesProcessor'],  # Librairies supplémentaires, le cas échéant
)

# Configuration du package
setup(
    name='GravForcesProcessor',
    version='1.0.0',
    author='Jonathan Savin',
    description='This package implements features to process Gravity forces for an OpenSim musculoskeletal model.',
    ext_modules=[extension_mod],
    py_modules=['GravForcesProcessor'],  # Modules Python supplémentaires à inclure
)
