from setuptools import setup, Extension

vmath = Extension(
	'vmath.vmath',
	sources = [
		'Source/VMath.cpp',
	]
)

setup(
	name = 'vmath',
	version = '0.1.0',
	description = 'vmath',
	url = 'https://github.com/cprogrammer1994/vmath',
	author = 'Szabolcs Dombi',
	author_email = 'cprogrammer1994@gmail.com',
	license = 'MIT',
	packages = ['vmath'],
	ext_modules = [vmath],
	platforms = ['win32', 'win64']
)
