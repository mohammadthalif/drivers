
SUBDIRS = common  i2c  input  tasklet  timer jiffies ctest

subdirs: clean 
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir clean;	\
	done
	
.PHONY: clean

clean:
	-@rm *~ -f
