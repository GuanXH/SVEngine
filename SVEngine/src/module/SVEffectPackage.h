//
// SVEffectPackage.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_EFFECTPACKAGE_H
#define SV_EFFECTPACKAGE_H


#include "SVModuleBase.h"
namespace sv{
    
    class SVEffectUnit : public SVGBase{
    public:
        SVEffectUnit(SVInst* _app);
        
        ~SVEffectUnit();
        
        void init(SVNodePtr _node);
        
        void destroy();
        
        SVNodePtr getNode();
        
        void setEnd(bool _end);
        
        bool isEnd();
    protected:
        SVNodePtr m_node;
        
        bool m_end;
    };
    
    class SVEffectPackage : public SVModuleBase {
    public:
        enum EFFECTANISTATE{
            EFFECT_ANI_WAIT = 0,
            EFFECT_ANI_BEGIN,
            EFFECT_ANI_END
        };
        SVEffectPackage(SVInst* _app);
        
        ~SVEffectPackage();
        
        virtual void init();
        
        virtual  void destroy();
        
        virtual void update(f32 _dt);
        
        virtual void open();
        
        virtual bool procEvent(SVEventPtr _event);
        
        void addEffectUnit(SVNodePtr _nodePtr);
        
        SVNodePtr getNode(cptr8 _name);
    protected:
        EFFECTANISTATE m_aniState;
        typedef SVArray<SVEffectUnitPtr> SVEFFECTUNITPOOL;
        SVEFFECTUNITPOOL m_effectUnitPool;
        SVLockPtr m_lock;
    };
    
    
}//!namespace sv

#endif /* SV_EFFECTPACKAGE_H */
