//
// SVCoordGridNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_COORD_GRID_NODE_H
#define SV_COORD_GRID_NODE_H

#include "SVNode.h"

namespace sv {
    
    namespace node{
        
        class SVCoordGridNode : public SVNode {
        public :
            SVCoordGridNode(SVInst *_app);
            
            ~SVCoordGridNode();
            
            void update(f32 dt);
            
            void render();
            
            f32 getUnit();
            
        protected:
            void _refreshUnit();
            
            f32 m_unit;
            
            SVRenderObjectPtr m_pRenderObj;
            
            SVRenderMeshPtr m_pMesh;
        };
        
    }//!namespace node
    
}//!namespace sv



#endif /* SV_COORD_GRID_NODE_H */
