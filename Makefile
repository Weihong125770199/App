
clean_LIBS = $(patsubst %,clean_%, $(LIBS))

PACKAGES = app-carplay lib-iap-accessory

clean_PACKAGES = $(patsubst %,clean_%, $(PACKAGES))

pkg_PACKAGES = $(patsubst %,pkg_%, $(PACKAGES))

.PHONY: all clean $(LIBS) $(clean_LIBS) $(PACKAGES) $(clean_PACKAGES) $(pkg_PACKAGES) app-pkg

all: $(LIBS) $(PACKAGES)

clean: $(clean_LIBS) $(clean_PACKAGES) 

app-pkg: $(pkg_PACKAGES)

$(PACKAGES):
ifeq ($(SVP_BUILD_DIR), )
	@echo "Pls setup env first!"
else
	mkdir -p $@/$(SVP_BUILD_DIR) && cd $@/$(SVP_BUILD_DIR) && \
	$(CMAKE) ../.. && $(MAKE) && make install
endif

$(clean_PACKAGES):
ifeq ($(SVP_BUILD_DIR), )
	@echo "Pls setup env first!"
else
	rm -rf $(subst clean_,,$@)/$(SVP_BUILD_DIR)
endif

$(pkg_PACKAGES):
ifeq ($(SVP_BUILD_DIR), )
	@echo "Pls setup env first!"
else
	cd $(subst pkg_,,$@) && ./pkg.sh
endif

$(LIBS):
ifeq ($(SVP_BUILD_DIR), )
	@echo "Pls setup env first!"
else
	mkdir -p $@/$(SVP_BUILD_DIR) && cd $@/$(SVP_BUILD_DIR) && \
	$(CMAKE) ../.. && $(MAKE) && make install
endif

$(clean_LIBS):
ifeq ($(SVP_BUILD_DIR), )
	@echo "Pls setup env first!"
else
	rm -rf $(subst clean_,,$@)/$(SVP_BUILD_DIR)
endif

