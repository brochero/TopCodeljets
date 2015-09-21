#include "Plots.h"

void Plots(TString plots="4Jets", TString sys="", bool EvtNorm=false){
  
  /****************
        Style
  ****************/
  gROOT->SetStyle("Plain");
  gStyle->SetOptFit(1000);
  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  
  gROOT->ProcessLine(".L /home/brochero/ttbar/TopCodeljets/tdrStyle.C");
  setTDRStyle();
  
  Int_t chatch = 1756;
  TColor *color = new TColor(chatch, 0.3, 0.5, 0.5, "", 0.45); // alpha = 0.5
  TString files  = dirnameIn + fl;  
  
  /****************
       Channel
  ****************/
  TString channel[3];
  channel[0] = "mujets";
  channel[1] = "ejets";  
  channel[2] = "lepjet"; 
  
 
  /****************
        Data
  ****************/ 
  std::vector<histos> DataMu;
  DataMu = loadhistograms(plots, files + "_DataSingleMu");
  std::vector<histos> DataEG;
  DataEG = loadhistograms(plots, files + "_DataSingleEG");
  std::vector<histos> Data;
  Data = addhistograms(DataMu, DataEG);
  setuphistograms(Data, kBlack);

  /****************
    ttbar Signal
  ****************/ 
  std::vector<histos> ttbar_0;
  ttbar_0 = loadhistograms(plots, files + "_ttbar-PowhegPythia");
  setuphistograms(ttbar_0, kRed+1);

  std::vector<histos> ttbar_1;
  ttbar_1 = loadhistograms(plots, files + "_ttbar-MCatNLO");
  setuphistograms(ttbar_1, kRed+2);

  std::vector<histos> ttbar_2;
  ttbar_2 = loadhistograms(plots, files + "_ttbar-Madgraph");
  setuphistograms(ttbar_2, kRed+3);

  /****************
       Z+Jets
  ****************/ 
  std::vector<histos> ZJets;
  ZJets = loadhistograms(plots, files + "_ZJets");
  setuphistograms(ZJets, kAzure-2);

  /****************
         VV
  ****************/ 
  std::vector<histos> WW;
  WW = loadhistograms(plots, files + "_WW");
  std::vector<histos> WZ;
  WZ = loadhistograms(plots, files + "_WZ");
  std::vector<histos> ZZ;
  ZZ = loadhistograms(plots, files + "_ZZ");
  std::vector<histos> VV;
  VV = addhistograms(WW, WZ);
  VV = addhistograms(VV, ZZ);
  setuphistograms(VV, kYellow-3);

  /****************
     Single Top
  ****************/ 
  std::vector<histos> tW;
  tW = loadhistograms(plots, files + "_tW");
  std::vector<histos> tbarW;
  tbarW = loadhistograms(plots, files + "_tbarW");
  std::vector<histos> t_tch;
  t_tch = loadhistograms(plots, files + "_t-tchannel");
  std::vector<histos> tbar_tch;
  tbar_tch = loadhistograms(plots, files + "_tbar-tchannel");
  std::vector<histos> Single_top;
  Single_top = addhistograms(tW, tbarW);
  Single_top = addhistograms(Single_top, t_tch);
  Single_top = addhistograms(Single_top, tbar_tch);
  setuphistograms(Single_top, kPink-3);

  /****************
       W+Jets
  ****************/ 
  std::vector<histos> WJets;
  WJets = loadhistograms(plots, files + "_WJets");
  setuphistograms(WJets, kGreen-3);

  /****************
     ttbar Bkg
  ****************/ 
  std::vector<histos> ttbar_bkg;
  ttbar_bkg = loadhistograms(plots, files + "_ttbar-PowhegPythiaBkg");
  setuphistograms(ttbar_bkg, kViolet-3);

  /****************
        QCD
  ****************/ 
  std::vector<histos> QCD;
  QCD = loadhistograms(plots, files + "_QCD-MuEnr");
  setuphistograms(QCD, kOrange-3);

  /****************
       Stacks
  ****************/ 
  std::vector<histos> Stack_bkg;
  std::vector<histos> Stack;
  histos st_bkg;
  histos st;
  for(unsigned int h=0; h<WJets.size(); h++){
    TString variable;
    for(int ch=0; ch<3; ch++){
      st.mc[ch]     = new THStack(variable, "");
      st_bkg.mc[ch] = new THStack(variable, "");
      st.mc[ch]->SetHistogram( (TH1F*)WJets[h].hist[ch]->Clone());
      st_bkg.mc[ch]->SetHistogram( (TH1F*)WJets[h].hist[ch]->Clone());
    }
    Stack.push_back(st);
    Stack_bkg.push_back(st_bkg);
  }
  
  //-------------------------------------------------------
  // Background Stack
  Stack_bkg = addstack(Stack_bkg, WJets);
  Stack_bkg = addstack(Stack_bkg, QCD);
  Stack_bkg = addstack(Stack_bkg, Single_top);
  Stack_bkg = addstack(Stack_bkg, VV);
  Stack_bkg = addstack(Stack_bkg, ttbar_bkg);
  Stack_bkg = addstack(Stack_bkg, ZJets);

  //-------------------------------------------------------
  // Stack
  Stack = addstack(Stack, WJets);
  Stack = addstack(Stack, QCD);
  Stack = addstack(Stack, Single_top);
  Stack = addstack(Stack, VV);
  Stack = addstack(Stack, ttbar_bkg);
  Stack = addstack(Stack, ZJets);
  Stack = addstack(Stack, ttbar_0);

  //-------------------------------------------------------
  // other ttbar Generators
  ttbar_1 = addhistograms(ttbar_1, Stack_bkg);
  ttbar_2 = addhistograms(ttbar_2, Stack_bkg);

  
  /****************
     Draw Histos
  ****************/ 
  TCanvas *histocanvas;
  histocanvas = new TCanvas("plots", "Plots");
  
  for(unsigned int h=0; h<WJets.size(); h++){
    for(int ch=0; ch<3; ch++){
      
      histocanvas->Divide(1,2);
      
      TPad    *pad[2];
      //Plot Pad
      pad[0] = (TPad*)histocanvas->GetPad(1);
      pad[0]->SetPad(0.01, 0.23, 0.99, 0.99);
      pad[0]->SetTopMargin(0.1);
      pad[0]->SetRightMargin(0.04);
      
      //Ratio Pad
      pad[1] = (TPad*)histocanvas->GetPad(2);
      pad[1]->SetPad(0.01, 0.02, 0.99, 0.3);
      gStyle->SetGridWidth(0.5);
      gStyle->SetGridColor(14);
      pad[1]->SetGridx();
      pad[1]->SetGridy();
      pad[1]->SetTopMargin(0.05);
      pad[1]->SetBottomMargin(0.4);
      pad[1]->SetRightMargin(0.04);
      
      //-------------------------------------------------------
      // Stack
      pad[0]->cd();

      Stack[h].mc[ch]->Draw("hist");

      Stack[h].mc[ch]->GetYaxis()->SetTitle("Events");
      Stack[h].mc[ch]->GetYaxis()->SetTitleOffset(1.2);
      Stack[h].mc[ch]->GetYaxis()->SetTitleSize(0.07);
      Stack[h].mc[ch]->GetYaxis()->SetLabelSize(0.055);
      Stack[h].mc[ch]->GetYaxis()->SetNdivisions(607);
      //Stack[h].mc[ch]->GetYaxis()->SetLabelSize(0.05);
      TGaxis *hYaxis = (TGaxis*)Stack[h].mc[ch]->GetYaxis();
      //hYaxis->SetMaxDigits(3);
      Stack[h].mc[ch]->GetXaxis()->SetLabelSize(0.0);
      Stack[h].mc[ch]->GetXaxis()->SetTitle("");

      float maxh = Data[h].hist[ch]->GetMaximum();
      if(maxh < Stack[h].mc[ch]->GetMaximum()) maxh = Stack[h].mc[ch]->GetMaximum();
      Stack[h].mc[ch]->SetMaximum(1.7*maxh);
      
      //-------------------------------------------------------
      // Band error
      TGraphErrors *thegraph = new TGraphErrors(Stack[h].hist[ch]);
      thegraph->SetName("thegraph");
      thegraph->SetFillStyle(1001);
      thegraph->SetFillColor(chatch);
      thegraph->SetLineColor(chatch);

      thegraph->Draw("e2SAME");

      //-------------------------------------------------------
      // Other ttbar generators
      ttbar_1[h].hist[ch]->SetLineColor(6);
      ttbar_1[h].hist[ch]->SetLineStyle(2);
      ttbar_1[h].hist[ch]->SetFillColor(0);
      ttbar_1[h].hist[ch]->Draw("histoSAME");

      ttbar_2[h].hist[ch]->SetLineColor(8);
      ttbar_2[h].hist[ch]->SetLineStyle(4);
      ttbar_2[h].hist[ch]->SetFillColor(0);
      ttbar_2[h].hist[ch]->Draw("histoSAME");
      //-------------------------------------------------------
      // Data Histogram
      Data[h].hist[ch]->SetMarkerStyle(20);
      Data[h].hist[ch]->SetMarkerSize(0.7);

      Data[h].hist[ch]->Draw("SAME");

      /***********************
             Legends
      ***********************/
      TLegend *leg;
      float legx1=0.76;
      float legy1=0.54;
      float legx2=0.90;
      float legy2=0.87;
      leg = new TLegend(legx1,legy1,legx2,legy2);
      leg->SetFillColor(0);
      leg->SetLineColor(1);
      leg->SetTextFont(62);
      leg->SetTextSize(0.03);

      leg->AddEntry(Data[h].hist[ch],"Data","PL");
      leg->AddEntry(ttbar_0[h].hist[ch],"t#bar{t} Signal","F");
      leg->AddEntry(ZJets[h].hist[ch],"Z+Jets","F");
      leg->AddEntry(ttbar_bkg[h].hist[ch],"t#bar{t} Bkg","F");
      leg->AddEntry(VV[h].hist[ch],"VV","F");
      leg->AddEntry(Single_top[h].hist[ch],"Single t","F");
      leg->AddEntry(QCD[h].hist[ch],"QCD","F");
      leg->AddEntry(WJets[h].hist[ch],"W+Jets","F");
      leg->AddEntry("thegraph","Uncertainty","F");
      leg->AddEntry((TObject*)0,"","");
      leg->AddEntry(ttbar_1[h].hist[ch],"MC@NLO","L");
      leg->AddEntry(ttbar_2[h].hist[ch],"Madgraph","L");

      leg->Draw("SAME");
      //-------------------------------------------------------
      // CMS
      TString htitleCMSChannel[3];
      htitleCMSChannel[0] = "#mu^{#pm}+jets channel";
      htitleCMSChannel[1] = "e^{#pm}+jets channel";
      htitleCMSChannel[2] = "l^{#pm}+jets channel";
      
      titlePr  = new TLatex(-20.,50.,"Preliminary");
      titlePr->SetNDC();
      titlePr->SetTextAlign(12);
      titlePr->SetX(0.25);
      titlePr->SetY(0.93);
      titlePr->SetTextColor(2);
      titlePr->SetTextFont(42);
      titlePr->SetTextSize(0.05);
      titlePr->SetTextSizePixels(24);
      titlePr->Draw("SAME");
      
      title  = new TLatex(-20.,50.,"CMS #sqrt{s} = 13TeV, L = 42 pb^{-1}(50ns)");
      title->SetNDC();
      title->SetTextAlign(12);
      title->SetX(0.20);
      title->SetY(0.83);
      title->SetTextFont(42);
      title->SetTextSize(0.05);
      title->SetTextSizePixels(24);
      title->Draw("SAME");
      
      chtitle  = new TLatex(-20.,50.,htitleCMSChannel[ch]);
      chtitle->SetNDC();
      chtitle->SetTextAlign(12);
      chtitle->SetX(0.20);
      chtitle->SetY(0.75);
      chtitle->SetTextFont(42);
      chtitle->SetTextSize(0.05);
      chtitle->SetTextSizePixels(24);
      chtitle->Draw("SAME");

      /***********************
               Ratio
      ***********************/    
      pad[1]->cd();
      
      //-------------------------------------------------------
      //Graph Ratio Clone
      TH1F *Ratio;
      Ratio = (TH1F*)Data[h].hist[ch]->Clone();
      Ratio->Divide(Stack[h].hist[ch]);

      TH1F *RatioSyst;
      RatioSyst = (TH1F*)Data[h].hist[ch]->Clone();
      RatioSyst->Divide(Stack[h].hist[ch]); // Should be the histogram with the Total Syst. Unc.
      std::vector<double> ratioContent;
      for(unsigned int b_r = 1; b_r <= RatioSyst->GetNbinsX(); b_r++){
	RatioSyst->SetBinContent(b_r,1.0);
	//RatioSyst->SetBinError(b_r,0.15); // Tempotal!!!
      }      

      Ratio->SetMarkerStyle(20);
      Ratio->SetMarkerSize(0.5);
      Ratio->SetMarkerColor(1);
      Ratio->SetLineColor(1);
      Ratio->SetLineWidth(1);
      Ratio->SetMaximum(2);
      Ratio->SetMinimum(0);
      Ratio->SetTitle("");
      
      Ratio->GetYaxis()->SetTitle("Obs/Exp");
      Ratio->GetYaxis()->CenterTitle();
      Ratio->GetYaxis()->SetTitleOffset(0.45);
      Ratio->GetYaxis()->SetTitleSize(0.16);
      Ratio->GetYaxis()->SetLabelSize(0.15);
      Ratio->GetYaxis()->SetNdivisions(402);
      Ratio->GetXaxis()->SetNdivisions(509);
      Ratio->GetXaxis()->SetTitleOffset(1.1);
      Ratio->GetXaxis()->SetLabelSize(0.20);
      Ratio->GetXaxis()->SetTitleSize(0.16);
      
      Ratio->SetMinimum(0.6);
      Ratio->SetMaximum(1.4);
      
      TGraphErrors *thegraphRatioSyst = new TGraphErrors(RatioSyst);
      thegraphRatioSyst->SetFillStyle(1001);
      thegraphRatioSyst->SetFillColor(chatch);
      thegraphRatioSyst->SetName("thegraphRatioSyst");
      
      //-------------------------------------------------------
      //Graph Ratio other ttbar generators
      TH1F *Ratio_1;
      Ratio_1 = (TH1F*)Data[h].hist[ch]->Clone();
      Ratio_1->Divide(ttbar_1[h].hist[ch]);
      Ratio_1->SetLineColor(6);
      Ratio_1->SetLineStyle(2);
      Ratio_1->SetLineWidth(2);
      Ratio_1->SetFillColor(0);

      TH1F *Ratio_2;
      Ratio_2 = (TH1F*)Data[h].hist[ch]->Clone();
      Ratio_2->Divide(ttbar_2[h].hist[ch]);
      Ratio_2->SetLineColor(8);
      Ratio_2->SetLineStyle(4);
      Ratio_2->SetLineWidth(2);
      Ratio_2->SetFillColor(0);

      //-------------------------------------------------------
      // Draw Ratios
      Ratio->Draw();
      thegraphRatioSyst->Draw("e2");
      Ratio->Draw("histpSAME");
      Ratio_1->Draw("histSAME");
      Ratio_2->Draw("histSAME");
            
      /***********************
            Save Histos
      ***********************/    
      TString dirfigname_pdf=dirnameIn + "figures_" + fl + "/pdf/";
      // make a dir if it does not exist!!
      gSystem->mkdir(dirfigname_pdf,       kTRUE);
      histocanvas->SaveAs(dirfigname_pdf + WJets[h].hist[ch]->GetName() + ".pdf");
      
      // clear Canvas
      histocanvas->Clear();    

    }
  }
  
} //end Plots.C

void setuphistograms(std::vector<histos> histos, int color){
  
  for(unsigned int h = 0; h < histos.size(); h++){
    for(unsigned int ch=0; ch<3; ch++){  
      
      // Overflows in the last bin
      histos[h].hist[ch]->SetBinContent(histos[h].hist[ch]->GetNbinsX(),
					(histos[h].hist[ch]->GetBinContent(histos[h].hist[ch]->GetNbinsX()+1) + 
					 histos[h].hist[ch]->GetBinContent(histos[h].hist[ch]->GetNbinsX())
					 )
					);
      // Set overflows to 0
      histos[h].hist[ch]->SetBinContent(histos[h].hist[ch]->GetNbinsX()+1, 0);

      // Style
      if(color == kRed+1) histos[h].hist[ch]->SetLineColor(1); // Except ttbar
      else histos[h].hist[ch]->SetLineColor(color);
      histos[h].hist[ch]->SetFillColor(color);
      histos[h].hist[ch]->SetFillStyle(1001);

    }    
  }    
}

std::vector<histos> addhistograms(std::vector<histos> histos_0, std::vector<histos> histos_1){

  std::vector<histos> sum;
  histos histos;

  for(unsigned int h = 0; h < histos_0.size(); h++){
    for(unsigned int ch=0; ch<3; ch++){  
      histos.hist[ch] = (TH1F*)histos_0[h].hist[ch]->Clone();
      histos.hist[ch]->Add(histos_0[h].hist[ch], histos_1[h].hist[ch]);
    }
    sum.push_back(histos);
  }

  return sum;
}

std::vector<histos> addstack(std::vector<histos> stack_0, std::vector<histos> histos_0){

  for(unsigned int h = 0; h < histos_0.size(); h++){
    for(unsigned int ch=0; ch<3; ch++){
      stack_0[h].mc[ch]->Add(histos_0[h].hist[ch]); // add histo to stack
      stack_0[h].hist[ch] = (TH1F*) stack_0[h].mc[ch]->GetStack()->Last()->Clone(); // create histo with the final stack
    }
  }
  
  return stack_0;
}

std::vector<histos> loadhistograms(TString plots, TString namefile){

  TFile *file=NULL; // new TFile(namefile);
  file = TFile::Open(namefile + ".root");
  
  if(!file){
    std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl;
    std::exit(0);
  }
  
  std::vector<histos> sample;
  histos histofile;
  
  TString channel[3];
  channel[0]="mujets";
  channel[1]="ejets";
  channel[2]="lepjets";
  
  std::vector<TString> histoname;
  
  // Histograms
  histoname.push_back("hPV");
  histoname.push_back("hMET");
  histoname.push_back("hLepPt");
  histoname.push_back("hLepEta");
  histoname.push_back("hLepPhi");
  histoname.push_back("hNJets");
  histoname.push_back("hNBtagJets");

  for(unsigned int h=0; h<histoname.size(); h++){
    for(unsigned int ch=0; ch<2; ch++) histofile.hist[ch] = (TH1F*)file->Get(histoname[h] + "_" + channel[ch] + "_" + plots);
    // lep + jets
    histofile.hist[2] = (TH1F*)histofile.hist[0]->Clone();
    histofile.hist[2]->Add(histofile.hist[0], histofile.hist[1]);
    histofile.hist[2]->SetName(histoname[h] + "_" + channel[2] + "_" + plots);
    
    sample.push_back(histofile);
    
  }  

  cout << "All the histograms from " << namefile << ".root have been loaded successfully!!!"  << endl; 
  return sample;
}

