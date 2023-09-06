// ******************************************************
// in the main loop;
  bool IsBatt = 0;
  IsBatt =  battery_monitor_init();
  double battV= 0.0;

// in the while loop
  battV= adc_send();
  printf("%f\n",battV); 
// ******************************************************
