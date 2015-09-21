# TopCodeljets
Code for the Measurement of the ttbar Xsec in the lepton + Jets channel


## General Comments
Before to run this code, it is important to clarify:

1. Name files are very important. They must keep a defined structure.

   - The output of the `TtbarSingleLepton.C`: 

     `Tree_LepJets_`"additional info of the sample"`_`"Luminosity in pb-1"`_`"SAMPLE"`.root`

     **Example:** 
```
     `Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_ttbar-PowhegPythia.root`	      
     `Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_DataSingleEG.root`
     `Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_WW.root`
```

2. You must change all the directory to your own home (**example**: *line 100 of TreeReader.C* ).

# 