setup:
	@pip install -e .[tests]

compile_ext:
	python setup.py build_ext -i

test: compile_ext
	@nosetests -s -v --with-yanc --with-coverage --cover-package=grimheaper tests/
