dir := $(shell pwd)
qmk_home := $(shell qmk env | grep QMK_HOME | sed 's/QMK_HOME=//g;s/"//g')
qmk_kyria_dir := ${qmk_home}/keyboards/splitkb/kyria/keymaps

kb := splitkb/kyria/rev2
km := wjossowski
config := -kb ${kb} -km ${km}

build: symlink
	qmk compile ${config}

rebuild: symlink clean images
	qmk compile -c ${config}

flash: build
	qmk flash ${config}

reflash: rebuild flash

keymap: build 
	qmk c2json ${config} --no-cpp -o ${dir}/dist/keymap.json ${dir}/keymap.c
	rm -f ${dir}/dist/*.png
	docker-compose up --exit-code-from cypress

clean:
	$(MAKE) clean -C gfx 

images:
	$(MAKE) images -C gfx 

qmk_rtfm := "Follow these instructions: https://docs.qmk.fm/ to properly set up your environment."
symlink: 
	@echo "Checking the programs required for the build are installed..."
	@echo "Checking if qmk is installed..."
	@(qmk --version >/dev/null 2>&1) || (echo "ERROR: qmk not found. ${qmk_rtfm}"; exit 1)
	@echo "Checking if qmk is properly configured..."
	@(qmk env | grep QMK_HOME >/dev/null 2>&1) || (echo "ERROR: qmk not configured. ${qmk_rtfm}"; exit 1)
	@(qmk env | grep QMK_HOME | sed 's/QMK_HOME=//g;s/"//g' | sed 's/.*/"&"/' >/dev/null 2>&1) || (echo "ERROR: QMK_HOME not configured. ${qmk_rtfm}"; exit 1)
	${shell cd ${qmk_kyria_dir} && ln -s ${dir} ${km}}
