# TopCodeljets
Code for the Measurement of the ttbar Xsec in the lepton + Jets channel


## General Comments
Before to run this code, it is important to clarify:

1. File names are very important. They must keep a defined structure.

   - The output of the `TtbarSingleLepton.C`: 

     `Tree_LepJets_`"additional info of the sample"`_`"Luminosity in pb-1"`_`"SAMPLE"`.root`

     **Example:** 
```
     `Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_ttbar-PowhegPythia.root`	      
     `Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_DataSingleEG.root`
     `Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_WW.root`
```

2. You must change all the directory to your own home (**example**: *line 100 of TreeReader.C* ).

# How to produce the Histograms (run TreeReader)

1. compile:
   
   `% make`

   It produces a `TreeReader.run` file.

2. Run:

   `% ./TreeReader.run -i Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_ttbar-PowhegPythia -o NameOfYourPreferences`

   more information:
   ```
   % ./TreeReader.run -h
   Options:
    -i inputfile  Input file without .root
    -o name in the output file "h_"
    -s create a file with the systematic uncertainty yields
    -tr SF Trigger Uncertainty
    -idiso SF ID/ISO Uncertainty
    -d Input file directory. Default directory: InputTrees
    -h                 displays this help message and exits 
   ``` 

3. Output: The output can be dicided in two parts: screen and histos.

   a. Screen: Contains information about sample, running time, yield and output.
   ```
   ./TreeReader.run -i Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_WJets -o NewPlots_v0
   ---------------------------------------------------------------------------------
   Signal: Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_WJets.root	
   -----------------------                                 -------------------------
   Normalization Factor = 0.10634
   ---------------------------------------------------------------------------------
   --- Processing: 6127205 events
   ==================================================] 100% 
   --- End of event loop: Real time 0:00:42, CP time 41.620
   --------  Acceptace  --------
   Number of RAW-mu+Jets events:
   lepton: 2407959
   4 Jets: 17567
   MET: 13642
   2 btag: 501
   --------  Efficiency  --------
   Number of Weigthed-mu+Jets events:
   lepton: 212386 +/- 136.868
   4 Jets: 1593.48 +/- 12.0225
   MET: 1224.35 +/- 10.4825
   2 btag: 43.9891 +/- 1.96529
   --------  Acceptace  --------
   Number of RAW-e+Jets events:
   lepton: 1965353
   4 Jets: 15955
   MET: 12417
   2 btag: 401
   --------  Efficiency  --------
   Number of Weigthed-e+Jets events: 
   lepton: 170856 +/- 121.874
   4 Jets: 1425.37 +/- 11.2844
   MET: 1099.71 +/- 9.86892
   2 btag: 35.3235 +/- 1.76397
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   Yields saved into TopResults/Yields_NewPlots_v0/WJets.h file
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   File saved as TopResults/hSF-NewPlots_v0_Tree_LepJets_v7-3-6_Spring15-bx50_40pb-1_WJets.root
   ```