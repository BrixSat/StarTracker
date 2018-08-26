/* ===================================================================== *
 *                                                                       *
   DISPLAY SYSTEM
 *                                                                       *
   =====================================================================
   every "disp menu function" needs three functions
   - void LCDML_DISP_setup(func_name)
   - void LCDML_DISP_loop(func_name)
   - void LCDML_DISP_loop_end(func_name)

   EXAMPLE CODE:
    void LCDML_DISP_setup(..menu_func_name..)
    {
      // setup
      // is called only if it is started

      // starts a trigger event for the loop function every 100 millisecounds
      LCDML_DISP_triggerMenu(100);
    }

    void LCDML_DISP_loop(..menu_func_name..)
    {
      // loop
      // is called when it is triggert
      // - with LCDML_DISP_triggerMenu( millisecounds )
      // - with every button status change

      // check if any button is presed (enter, up, down, left, right)
      if(LCDML_BUTTON_checkAny()) {
        LCDML_DISP_funcend();
      }
    }

    void LCDML_DISP_loop_end(..menu_func_name..)
    {
      // loop end
      // this functions is ever called when a DISP function is quit
      // you can here reset some global vars or do nothing
    }
   =====================================================================
*/

#define VALUE_X  75
#define VALUE_Y  13

#define MOTOR_SPEED_X 0
#define MOTOR_SPEED_Y 13

#define BOX_X 8
#define BOX_Y 51
#define INITIAL_VAR 13
#define INITIAL_VAR_PRINT_VALUE 12

#define MIN_VALUE 0
#define MAX_VALUE 100

#define MIN_VALUE_X 1
#define MIN_VALUE_Y 61

#define MAX_VALUE_X 110
#define MAX_VALUE_Y 61

#define FRAME_X1 7
#define FRAME_Y1 50
#define FRAME_X2 102
#define FRAME_Y2 102



// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_tuneC2)
// *********************************************************************
{
  // setup function
  u8g2.setFont(_LCDML_DISP_font);
  u8g2.firstPage();
  g_button_value = C1; //set to global value of C1
  do {

    u8g2.drawFrame(FRAME_X1, FRAME_X2, FRAME_Y1, FRAME_Y2);
    u8g2.drawStr(MIN_VALUE_X, MIN_VALUE_Y, MIN_VALUE); // minimum value STRING
    u8g2.drawStr(MAX_VALUE_Y, MAX_VALUE_Y, MAX_VALUE); //max value STRING
    u8g2.drawStr( MOTOR_SPEED_X, MOTOR_SPEED_Y, "Motor Speed:");
    char buf[17];
    sprintf (buf, "%0003d", C1);
    u8g2.drawStr(VALUE_X, VALUE_Y, buf);
       
    //draw the initial bar 
    u8g2.drawBox(BOX_X, BOX_Y, C1, INITIAL_VAR);

  } while ( u8g2.nextPage() );
  // Reset Button Value
  g_button_value = C1; 

}



void LCDML_DISP_loop(LCDML_FUNC_tuneC2)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
  if (LCDML_BUTTON_checkAny()) {
    if (LCDML_BUTTON_checkDown()) {
      // check if button up is pressed -- even though it says 'down'
      LCDML_BUTTON_resetDown(); // reset the down button
      if (C1 < MAX_VALUE) {
        //allow the user to roll past endpoints but don't do anything about it
        g_button_value++;
        C1++;
      } //if
      
      // update lcd content
      char buf[4];
      sprintf (buf, "%0003d", g_button_value);
      do {
        //print the value
        u8g2.drawStr( VALUE_X, VALUE_Y, buf);
        u8g2.drawBox(BOX_Y, BOX_Y, g_button_value, INITIAL_VAR);
      } while( u8g2.nextPage() );        
    } //if checkDown   
    
    if (LCDML_BUTTON_checkUp()) {
      LCDML_BUTTON_resetUp();
      if (C1 > 0) {
        //allow the user to roll past endpoints but don't do anything about it
        g_button_value--;
        C1--;
      } //if
      // update lcd content
      char buf[17];
      sprintf (buf, "%0003d", g_button_value);
      do {
        //print the value
        u8g2.drawStr( VALUE_X, VALUE_Y, buf);
        u8g2.setDrawColor(0);
        u8g2.drawBox((BOX_X+g_button_value),BOX_Y,(MAX_VALUE-g_button_value),INITIAL_VAR_PRINT_VALUE);
        u8g2.setDrawColor(1);

      } while( u8g2.nextPage() );  


    } //if checkUp

    if (LCDML_BUTTON_checkLeft()) {
      LCDML_BUTTON_resetLeft();
      LCDML_DISP_funcend();   
    } //if checkBack
  } //if checkAny
  
} //LCDML_DISP_loop



void LCDML_DISP_loop_end(LCDML_FUNC_tuneC2)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
