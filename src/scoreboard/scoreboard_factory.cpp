#include "scoreboard_factory.h"
#include "hw_scoreboard.h"
#include "usb_scoreboard.h"
#include "null_scoreboard.h"
#include "img_scoreboard.h"
#include "overlay_scoreboard.h"
#include "../io/logger.h"

IScoreboard *ScoreboardFactory::GetInstance(ScoreboardType type, ILogger *pLogger,
											SDL_Surface *(*pFuncGetActiveOverlay)(), bool bThayers,
											bool bUsingAnnunciator,
											unsigned int uWhichPort)
{
	IScoreboard *pRes = 0;

	switch (type)
	{
	default:	// NULL
		pRes = NullScoreboard::GetInstance();
		break;
	case IMAGE:
		pRes = ImgScoreboard::GetInstance();
		break;
	case OVERLAY:
		pRes = OverlayScoreboard::GetInstance(pFuncGetActiveOverlay, bThayers);
		break;
	case HARDWARE:	// Hardware scoreboard via parallel port
		pRes = HwScoreboard::GetInstance(uWhichPort, pLogger);
		break;
	case USB:	// Hardware scoreboard via USB
	        pRes = USBScoreboard::GetInstance();
		break;
	}

	// set the annunciator value while we're here
	if (pRes != NULL)
	{
		pRes->m_bUsingAnnunciator = bUsingAnnunciator;
	}

	return pRes;
}
