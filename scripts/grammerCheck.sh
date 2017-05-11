for i in `cat scripts/texFiles.txt`; do echo --------$i-------; ./latexgrammar.sh $PWD/$i; done
