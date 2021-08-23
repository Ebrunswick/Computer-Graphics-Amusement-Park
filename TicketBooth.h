/*	Author:			Evan Brunswick
 *	Filename:		TicketBooth.h
 *	Created Date:	03/08/2021
 *	
 *	Just a bare minimum simple ticket booth to get points for texture implememntation.
 */

#ifndef _TICKETBOOTH_H_
#define _TICKETBOOTH_H_

#include <FL/gl.h>

class TicketBooth {
private:	
	GLubyte display_list;   // The display list that does all the work.
	GLuint  texture_obj;    // The object for the grass texture.
	bool	initialized;

public:
	TicketBooth(void);
	~TicketBooth(void);

	bool Initialize(void);
	void Draw(void);


};


#endif 
