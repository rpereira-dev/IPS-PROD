all:
	# génération du Mainpage.dox
	echo "/*! \mainpage Projet Romain PEREIRA Clément GAVOILLE" > Mainpage.dox
	echo "*" >> Mainpage.dox
	cat ../README.md >> Mainpage.dox
	echo "*/" >> Mainpage.dox

	# génération de la documentation
	doxygen

clean:
	rm -rf html/
	rm -rf latex/

fclean: clean
