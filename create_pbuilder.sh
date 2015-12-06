#!/bin/sh

create_pbuilder()
{
	DISTRO=$1
	ARCH=$2
	BASETGZPATH=/var/cache/pbuilder/
	BASETGZ="$BASETGZPATH/$DISTRO-$ARCH.tgz"
	
	if [ -f $BASETGZ ]; then
		echo "Updating $BASETGZ"
		pbuilder --update --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH
	else
		echo "Creating $BASETGZ"
		pbuilder create --basetgz $BASETGZ --distribution $DISTRO --architecture $ARCH
	fi
	
	
}


create_pbuilder "wheezy" "i386"
create_pbuilder "wheezy" "amd64"

create_pbuilder "jessie" "i386"
create_pbuilder "jessie" "amd64"

