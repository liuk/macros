
void PipeInit() {}

double Pipe(PHG4Reco* g4Reco,
	    double radius,
	    const int absorberactive = 0,
	    int verbosity = 0) {

  double be_pipe_radius    = 2.0005; // 4.001 cm inner diameter from spec sheet
  double be_pipe_thickness = 0.0760; // 760 um based on spec sheet
  double be_pipe_length    = 80.0;   // +/- 40 cm

  double al_pipe_radius    = 2.0005; // same as Be pipe
  double al_pipe_thickness = 0.1600; // 1.6 mm based on spec
  double al_pipe_length    = 88.3;   // extension beyond +/- 40 cm
  
  if (radius > be_pipe_radius) {
    cout << "inconsistency: radius: " << radius 
	 << " larger than pipe inner radius: " << be_pipe_radius << endl;
    gSystem->Exit(-1);
  }
  
  gSystem->Load("libg4detectors.so");
  gSystem->Load("libg4testbench.so");

  // mid-rapidity beryillium pipe
  PHG4CylinderSubsystem *cyl = new PHG4CylinderSubsystem("BE_PIPE", 0);
  cyl->SetRadius(be_pipe_radius);
  cyl->SetLengthViaRapidityCoverage(false);
  cyl->SetLength(be_pipe_length);
  cyl->SetMaterial("G4_Be");
  cyl->SetThickness(be_pipe_thickness);
  cyl->SuperDetector("PIPE");
  if (absorberactive)  cyl->SetActive();
  g4Reco->registerSubsystem( cyl );

  // north aluminum pipe
  cyl = new PHG4CylinderSubsystem("N_AL_PIPE", 1);
  cyl->SetPosition(0.0,0.0,0.5*be_pipe_length+0.5*al_pipe_length+no_overlapp);
  cyl->SetRadius(al_pipe_radius);
  cyl->SetLengthViaRapidityCoverage(false);
  cyl->SetLength(al_pipe_length);
  cyl->SetMaterial("G4_Al");
  cyl->SetThickness(al_pipe_thickness);
  cyl->SuperDetector("PIPE");
  if (absorberactive)  cyl->SetActive();
  g4Reco->registerSubsystem( cyl );

  // south aluminum pipe
  cyl = new PHG4CylinderSubsystem("S_AL_PIPE", 2);
  cyl->SetPosition(0.0,0.0,-0.5*be_pipe_length-0.5*al_pipe_length-no_overlapp);
  cyl->SetRadius(al_pipe_radius);
  cyl->SetLengthViaRapidityCoverage(false);
  cyl->SetLength(al_pipe_length);
  cyl->SetMaterial("G4_Al");
  cyl->SetThickness(al_pipe_thickness);
  cyl->SuperDetector("PIPE");
  if (absorberactive)  cyl->SetActive();
  g4Reco->registerSubsystem( cyl );

  radius = be_pipe_radius + be_pipe_thickness;
  
  if (verbosity > 0) {
    cout << "=========================== G4_Pipe.C::Pipe() =============================" << endl;
    cout << " PIPE Material Description:" << endl;
    cout << "  inner radius = " << be_pipe_radius << " cm" << endl;
    cout << "  thickness = " << be_pipe_thickness << " cm" << endl;
    cout << "  outer radius = " << be_pipe_radius + be_pipe_thickness << " cm" << endl;
    cout << "  length = " << be_pipe_length << " cm" << endl;
    cout << "===========================================================================" << endl;
  }

  radius += no_overlapp;
  
  return radius; 
}
