#include<stdlib.h> 
#include<math.h>
#include<string.h>
#include<GL/glut.h>	// OpenGL Graphics Utility Library


// These three variables control the animation's state and speed.

static float Orbit = 0.0;
static float AnimateIncrement = 24.0;
GLfloat diffuseMaterial[4] = { 1.0, 0.0, 0.0, 1.0 };
// Time step for animation (hours)

const float DEG2RAD = 3.14159/180;


// glutKeyboardFunc is called below to set this function to handle
//		all normal key presses. 
static void Key_up(void)
{
    AnimateIncrement *= 2.0;			// Double the animation time step
}

static void Key_down(void)
{
    AnimateIncrement /= 2.0;			// Halve the animation time step
	
}
static void KeyPressFunc( unsigned char Key, int x, int y )
{
	switch ( Key ) {

	case 'q':	// Escape key
		exit(1);
	}
}

// glutSpecialFunc is called below to set this function to handle
//		all special key presses.  See glut.h for the names of
//		special keys.
static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {
	case GLUT_KEY_UP:		
		Key_up();
		break;
	case GLUT_KEY_DOWN:
		Key_down();
		break;
	}
}






void showMessage(GLfloat x, GLfloat y, GLfloat z, char *message)
{
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glTranslatef(x, y, z);
  glScalef(.0025, .003, .004);
  while (*message) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *message);
    message++;
  }
  glEnable(GL_LIGHTING);
  glPopMatrix();
}


/*
 * Animate() handles the animation and the redrawing of the
 *		graphics window contents.
 */
static void Display(void)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	// Clear the redering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update the animation state

        Orbit += AnimateIncrement/24.0;
		Orbit = Orbit - ((int)(Orbit/365))*365;
		
	
	// Clear the current matrix (Modelview)
    glLoadIdentity();

	// Back off eight units to be able to view from the origin.
    glTranslatef ( 0.0, 0.0, -8.0 );


	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
   glRotatef( 15.0, 1.0, 0.0, 0.0 );
   glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
   glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    // Draw the nucleus as a solid sphere
	glColor3f( 0.0, 0.6, 0.4 );
    glutSolidSphere( 0.8, 15, 15 );
showMessage(-0.5,-0.6,1.5,"Nucleus");
showMessage(-0.5,3.0,1.5,"Li ");


    // Draw the first electron
	// Position it around the nucleus and determine its position
	
    glRotatef( 360.0*Orbit/365.0, 0.0, 1.0, 0.0 );
    glTranslatef( 2.0, 0.0, 0.0 );
    glPushMatrix();// Save matrix state
	// Rotate the first electron on its axis.
	
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glColor3f( 0.2, 0.2, 1.0 );
    glutSolidSphere( 0.2, 10, 10);
	showMessage(0.3,0.0,0.0,"e-");// Draw the first electron as a solid sphere.
    glPopMatrix();				// Restore matrix state

	
	
	

	glPushMatrix();	
	// Save matrix state
	// Determine the rotation of second electron

	glTranslatef(-4.0,0.0,0.0);
	showMessage(0.3,0.0,0.0,"e-");
	// Draw the second electron as a solid sphere.
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glColor3f( 0.2, 0.2, 1.0 );
    glutSolidSphere( 0.2, 10, 10);
	glPopMatrix();	
	
	
	
	glPushMatrix();	
	showMessage(1.8,0.65,3.0,"e-");// Save matrix state
	//Determine rotation of third electron

	glTranslatef(1.5,0.65,3.0);
	// Draw the third electron as a solid sphere.
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glColor3f( 0.2, 0.2, 1.0 );
    glutSolidSphere( 0.2, 10, 10);
	glPopMatrix();	

	// Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();
	


	glutPostRedisplay();		// Request a re-draw for animation purposes

}

// Initialize OpenGL's rendering modes
void OpenGLInit(void)
{

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
}

// ResizeWindow is called when the window is resized
static void ResizeWindow(int w, int h)
{
    float aspectRatio;
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	glViewport( 0, 0, w, h );	// View port uses whole window
	aspectRatio = (float)w/(float)h;

	// Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 30.0 );

	// Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}


// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main( int argc, char** argv )
{
	// Need to double buffer for animation
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Create and position the graphics window
    glutInitWindowPosition( 50,50 );
    glutInitWindowSize( 600, 360 );
    glutCreateWindow( "Bohr's Atomic Model" );

	// Initialize OpenGL.
    OpenGLInit();

	// Set up callback functions for key presses
	glutKeyboardFunc( KeyPressFunc );
	glutSpecialFunc( SpecialKeyFunc );

	// Set up the callback function for resizing windows
    glutReshapeFunc( ResizeWindow );

	// Callback for graphics image redrawing
    glutDisplayFunc( Display );
	
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );

    return(0);			// Compiler requires this to be here. (Never reached)
}




