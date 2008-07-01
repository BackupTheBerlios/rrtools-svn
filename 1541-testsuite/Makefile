
DREAMASS = dreamass

test_files := $(patsubst %.asm,%.prg,$(wildcard tests/*.asm))
disk_files := $(patsubst %.list,%.d64,$(wildcard disks/*.list))


all: disks

framework: 1541-testsuite.prg

tests: $(test_files)

disks: framework tests prg2ul $(disk_files)

1541-testsuite.prg: 1541-testsuite.asm
	$(DREAMASS) -o $@ $<

tests/%.prg: tests/%.asm tests/1541-tests.inc
	$(DREAMASS) -Itests/ -o $@ $<

prg2ul: prg2ul.c
	$(CC) -o $@ $<

disks/%.d64: disks/%.list make_testdisk
	./make_testdisk $<

clean:
	rm -rf 1541-testsuite.prg
	rm -rf $(test_files)
	rm -rf prg2ul
	rm -rf $(disk_files)
