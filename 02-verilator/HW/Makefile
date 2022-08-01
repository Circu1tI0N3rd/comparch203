TOPMODULE=oneshot

.PHONY: help
help:
	@echo "make [option]"
	@echo "\tlint    run lint checks for syntax and violations"
	@echo "\tsview   view schematics"
	@echo "\tbuild   verilate and build modules"
	@echo "\tsim     run simulation"
	@echo "\twave    open waveforms"
	@echo "\tclean   clean the working folder"
	@echo "\thelp    print this help"

.PHONY: all
all: lint sim

.PHONY: sview
sview: $(TOPMODULE).svg
	open -a Firefox $(TOPMODULE).svg

$(TOPMODULE).svg: $(TOPMODULE).ys
	yosys $(TOPMODULE).ys
	netlistsvg -o $(TOPMODULE).svg $(TOPMODULE).json

.PHONY: lint
lint:
	@echo "-> LINTING"
	verilator -Wall -sv --lint-only $(TOPMODULE).sv --top-module $(TOPMODULE)

.PHONY: build
build: ./obj_dir/V$(TOPMODULE)
./obj_dir/V$(TOPMODULE): $(TOPMODULE).sv tb_$(TOPMODULE).cpp
	@echo "[1] -> VERILATING"
	verilator -Wall -sv -cc --trace-fst $(TOPMODULE).sv --top-module $(TOPMODULE) --exe tb_$(TOPMODULE).cpp
	@echo "[2] -> BUILDING"
	make -C obj_dir -f V$(TOPMODULE).mk V$(TOPMODULE)

.PHONY: sim
sim: ./obj_dir/V$(TOPMODULE)
	@echo "-> SIMULATING"
	./obj_dir/V$(TOPMODULE)

.PHONY: wave
wave: $(TOPMODULE).fst
	@echo "-> WAVEFORMS"
	@open $(TOPMODULE).fst

.PHONY: clean
clean:
	rm -rf obj_dir/
	rm -f *.fst
	rm -f *.json
	rm -f *.svg
