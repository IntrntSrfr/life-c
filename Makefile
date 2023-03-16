BUILD_DIR = .build

build:
	@mkdir -p .build
	@cd .build; \
		cmake ../src; \
		make; # --no-print-directory;

run:
	@cd .build; \
		./life-c
