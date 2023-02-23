VERSION = 0.1.1

main:
	gcc src/main.c -Wall -std=c99 -o uwulang

test:
	./uwulang test/hellOwOrld.uwu

install: clean package package-build
	sudo dpkg -i uwulang_$(VERSION)_all.deb

clean:
	rm uwulang || true
	rm -rf uwulang_$(VERSION)_all || true

package:
	@groff -man -Tascii uwulang.1 > uwulang.1.txt
	@install -D -m 644 uwulang.1.txt uwulang_$(VERSION)_all/usr/share/man/man1/uwulang.1.gz
	@rm uwulang.1.txt
	@gcc src/main.c -Wall -std=c99 -o uwulang
	@mkdir uwulang_$(VERSION)_all/usr/bin
	@cp ./uwulang uwulang_$(VERSION)_all/usr/bin/uwulang
	@mkdir uwulang_$(VERSION)_all/DEBIAN
	@cp DEBIAN/control uwulang_$(VERSION)_all/DEBIAN/control

# run package build
package-build:
	@dpkg-deb --build uwulang_$(VERSION)_all/
