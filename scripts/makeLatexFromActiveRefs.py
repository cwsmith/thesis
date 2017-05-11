#!/usr/bin/env python
# -*- coding: utf-8 -*-
# vim:set softtabstop=2 shiftwidth=2:

import sys
import getopt

def usage():
  print('-refs <list of refs> ')

def getArgs():
  shortargs=None
  longargs=['refs=']
  try:
    opts,args = getopt.getopt(sys.argv[1:],shortargs,longargs)
  except getopt.GetoptError as err:
    print(str(err))
    usage()
    sys.exit(1)

  options = dict(opts)
  print("options ", options)
  for la in longargs:
    arg='--'+la.strip('=')
    if arg not in options:
      print(arg, " not found")
      usage()
      sys.exit(1)
  return options

#### main ####
options = getArgs();
refsFile = options['--refs']

header='''\documentclass{article}
\\usepackage{cite}
\\usepackage{url}
\\title{\\LARGE \\bf Checking Reference Formatting}
\\begin{document}
\\maketitle'''

footer='''\\bibliographystyle{scorec-refs/IEEEtran_rpi}
\\bibliography{scorec-refs/scorec-refs}
\\end{document}'''

print(refsFile)

typesToRefs={}
with open(refsFile) as f:
  content = f.readlines()
  for line in content:
    if '@' in line:
      refType=line.strip().split('{')[0].lstrip('@')
      ref=line.strip().split('{')[1].rstrip(',')
      if refType not in typesToRefs.keys():
        print('adding reftype', refType)
        typesToRefs[refType] = []
      typesToRefs[refType].append(ref)

totalrefs=0
for reftype, refs in typesToRefs.items():
  outfilename = 'refs_' + reftype + '.tex'
  print(outfilename)
  outfile = open(outfilename, 'w')
  totalrefs = totalrefs + len(refs)
  outfile.write(header+"\n")
  for ref in refs:
    outfile.write("\cite{" + ref + "}" + "\n")
  outfile.write(footer + "\n")
  outfile.close()

print(totalrefs)
