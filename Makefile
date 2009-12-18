
SUBDIRS = common  i2c  input  tasklet  timer jiffies

subdirs: clean 
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir clean;	\
	done
	
.PHONY: clean

clean:
	-@rm *~ -f
