versions=('2016' '2016.5' '2017' '2018')
op_system='linux'
plugin_name='shellMod'
make_dir='/home/none/Desktop/ShellMod/make/build/'$op_system'/'
destination_dir='/home/none/Desktop/ShellMod/build/'$op_system'/'

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo ""
printf "${RED}[Starting $plugin_name build...]${NC}\n"
echo ""

for i in "${versions[@]}"
	do
		printf '[Searching]: '$make_dir$i'\n'

		if [ -e $make_dir$i ]
		then
			printf "${GREEN}[Found Maya v$i]${NC}\n"
			cmake --build $make_dir$i --config Release

			bundle_file=$make_dir$i'/src/'$plugin_name'.so'

			if [ -e $bundle_file ]
			then
				mkdir -p $destination_dir$i
				
				cp $bundle_file $destination_dir$i
			fi
			
		fi
		
	done


echo ""
printf "${GREEN}[Build finished...]${NC}\n"
echo ""
