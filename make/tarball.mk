# Tarball module for "c1" programs.
TARTARGETS = dist $(TARGZARC) $(TARARC) $(TARDIR)
.SILENT: $(TARTARGETS)

dist : $(TARGZARC)

$(TARGZARC) :  $(TARARC)
	$(GZIP) $(TARARC) $(GZARC)

$(TARARC) : $(TARDIR)
	$(TAR) $(TARARC) $(TARDIR)

$(TARDIR) : 
	$(MKDIR) $(TARDIR)
	$(CP) $(subst $(TARDIR),,$(wildcard *)) $(TARDIR)
