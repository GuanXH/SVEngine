//
// SVEventDef
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_EVENTDECLARE_H
#define SV_EVENTDECLARE_H

#include "../base/SVPreDeclare.h"

namespace sv {
    
    DECLARE_SHAREPTR(SVEvent);
    DECLARE_SHAREPTR(SVRecycleEvent);
    DECLARE_SHAREPTR(SVPersonEvent);
    DECLARE_SHAREPTR(SVFaceShapeEvent);
    DECLARE_SHAREPTR(SVAnimateEvent);
    DECLARE_SHAREPTR(SVResetTimeStateEvent);
    DECLARE_SHAREPTR(SVParseEvent);
    DECLARE_SHAREPTR(SVPickGetEvent);
    DECLARE_SHAREPTR(SVPickGetNothingEvent);
    DECLARE_SHAREPTR(SVPickLoseEvent);
    DECLARE_SHAREPTR(SVPickChangeEvent);
    DECLARE_SHAREPTR(SVReadyEnterEvent);
    DECLARE_SHAREPTR(SVPacketEndEnterEvent);
    DECLARE_SHAREPTR(SVPacketUnitEndEvent);
    DECLARE_SHAREPTR(SVPacketCloseEvent);
    //
    DECLARE_SHAREPTR(SVEventVideo);
    DECLARE_SHAREPTR(SVEventVideoCtrl);
    DECLARE_SHAREPTR(SVEventVideoStatus);
    DECLARE_SHAREPTR(SVEventMixBegin);
    DECLARE_SHAREPTR(SVEventMixEnd);
    //
    DECLARE_SHAREPTR(SVTouchEvent);
    DECLARE_SHAREPTR(SVPickEvent);
    DECLARE_SHAREPTR(SVCameraOrenEvent);
    DECLARE_SHAREPTR(SVReactEvent);
    //
    DECLARE_SHAREPTR(SVEventThread);
    
}

#endif //SV_EVENTDECLARE_H
