NOT_SUPPORT := lle cir_queue Makefile libs include obj
SUPPORTED := $(filter-out $(NOT_SUPPORT), $(wildcard *))
target ?= $(SUPPORTED)
mode ?= debug

.PHONY := all release debug test clean

all : release debug

release:
	@$(foreach sup, $(target), $(MAKE) -C ./$(sup)/ release ;)

debug: 
	@$(foreach sup, $(target), $(MAKE) -C ./$(sup)/ debug ;)

test: debug 
	@$(foreach sup, $(target), $(MAKE) -C ./$(sup)/ test ;)

clean: 
	@$(foreach sup, $(target), $(MAKE) -C ./$(sup)/ clean ;)


$(SUPPORTED) :	 
	@$(MAKE) -C ./$(sup) $(mode)
