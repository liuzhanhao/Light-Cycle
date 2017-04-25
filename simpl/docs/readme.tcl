Here is the procedure I followed to upgrade Tcl/Tk and get
the fctclx library installed and running.

1) Make a home for the downloads
mkdir /home/tcl
enter into kde and go to www.scriptics.com
find the software download area and ftp
	tcl8.0.4.tar.gz
	tk8.0.4.tar.gz
to this directory

2) Install the new version of tcl
cd /home/tcl
gunzip tcl8.0.4.tar.gz
tar -xvf tcl8.0.4.tar
cd tcl8.0.4/unix
./configure
make
make install
cd /usr/bin
ln -fs /usr/local/bin/tclsh8.0 tclsh
tclsh
%info tclversion
%exit

You should see 8.0 as the version number.

3) Install the new version of Tk 
cd /home/tcl
gunzip tk8.0.4.tar.gz
tar -xvf tk8.0.4.tar
cd tk8.0.4/unix
./configure
make
make install
cd /usr/bin
ln -fs /usr/local/bin/wish8.0 wish

4) Install the simpl.tar.gz package and build the simpl tcl library extension
be sure that you have an enviroment variable defined
	SIMPL_HOME=/root/simpl   (or whatever)

cd $SIMPL_HOME
cd ..
mcopy a:/simpl.tar.gz .
tar -zxvf simpl.tar.gz
buildsimpl

5) Configure the simpl tcl library extension as a package
cd $SIMPL_HOME/lib
ln -s $SIMPL_HOME/tcl/lib/libfctclx.so.1 libfctclx.so
cd /usr/local/lib
mkdir simpl 
cd simpl
ln -s $SIMPL_HOME/lib/libfctclx.so .
tclsh
%pkg_mkIndex /usr/local/lib/simpl *.so
%exit


-------------------------
FCsoftware Inc. 1998
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------
