# clone the repos listed as submodules

```
git submodule init
git submodule update
```

# build

```
latexmk -r latexmkrc.<OS>
latexmk -pdf -outdir=anc announcement_wrapper
cd presentation
latexmk -r latexmkrc.<OS>
```

# Create a diff marked pdf

## download git-latexdiff

wget https://gitlab.com/git-latexdiff/git-latexdiff/raw/master/git-latexdiff

make it executable
```
chmod +x get-latexdiff
```

## run the diff script
```
./scripts/do_gitlatexdiff.sh <old sha1> <new sha1>
```

## find active references
First, build the document so that out/cws-thesis.bbl exists.  Then, run the
following script from the thesis directory:
```
./scripts/getActiveRefs.sh
```

## check references
Run the following scripts to create tex files with each type of reference:
```
./scripts/getActiveRefs.sh  > refs.txt
./scripts/makeLatexFromActiveRefs.py --refs refs.txt
```
Run latexmk to build the resulting latex files:
```
latexmk -r latexmkrc.refs.linux
```


## find grammer issues
First, install language tool as described here:
https://danious.wordpress.com/2013/10/07/grammar-latex/

An install on scorec is available here:
```
/users/cwsmith/software/languageTool
```

Create a symbolic link to the latexgrammer.sh script in the thesis directory:
```
ln -s /users/cwsmith/software/languageTool/latexgrammer.sh
```

Next, create a list of all active tex files and call it 'scripts/texFiles.txt'.  Then
run the following script from the thesis directory:
```
./scripts/grammerCheck.sh
```
