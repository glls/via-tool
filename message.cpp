//---------------------------------------------------------------------------
#include "message.h"
//---------------------------------------------------------------------------
static char *msg_table_en[] = {
	"Failed to open clipboard",
	"Failed to get clipboard ownership",
	"Now working.. %d %%",
	"No error",
	"Failed to open %s",
	"Failed to get %s information",
	"%s has no video stream",
	"Failed to get %s video stream information",
	"Not enough memory",
	"Failed to load frame data",
	"Reached first frame",
	"Reached last frame",
	"Failed to find I-picture",
	"Frame %I64d is not I-picture nor closed-gop B-picture",
	"Frame %I64d is B-picture",
	"Max: %I64d",
	"Max: %s",
	"Failed to store %s",
};

char **msg_table[] = {
	msg_table_en
};
//---------------------------------------------------------------------------
