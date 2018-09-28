//
// SVNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_NODE_H
#define SV_NODE_H

#include "SVNodeDef.h"
#include "../mtl/SVMtlDeclare.h"
#include "../rendercore/SVRenderDef.h"
#include "../core/SVVertDef.h"
#include "../base/SVMat4d.h"
#include "../base/SVVec3.h"
#include "../base/SVBounds.h"
#include "../base/SVPreDeclare.h"
#include "../event/SVEventProc.h"
#include "../detect/SVPerson.h"
#include "../base/SVDataSwap.h"

namespace sv {
    
    namespace node{
        
        //
        class SVNode : public SVEventProc {
            friend class SVActBase;
        public:
            SVNode(SVInst *_app);
            
            ~SVNode();
            
            bool operator <(const SVNode& rhs) const{
                return m_iZOrder < rhs.m_iZOrder;
            }
            bool operator >(const SVNode& rhs) const{
                return m_iZOrder > rhs.m_iZOrder;
            }

            virtual void enter();
            
            virtual void exit();
            
            void deep_update(f32 dt);
            
            void deep_visit(SVVisitorBasePtr _visit);
            
            FMat4& getLocalMat();
            
            FMat4& getAbsoluteMat();
            
            FMat4& getIAbsoluteMat();
            
            void getWorldMatrix(FMat4& outMat);
            
            virtual void setPosition(f32 x, f32 y, f32 z);
            
            virtual void setRotation(f32 x, f32 y, f32 z);
            
            virtual void setScale(f32 x, f32 y, f32 z);
            
            virtual void setPosition(FVec3& _pos);
            
            virtual void setRotation(FVec3& _rot);
            
            virtual void setScale(FVec3& _scale);
            
            void setbeSelect(bool _select);
            
            void setcanSelect(bool _select);
            
            void setRSType(RENDERSTREAMTYPE _retype);
            
            void setdrawAABB(bool _drawaabb);
            
            bool getDrawAABB();
            
            SVNodePtr getParent();
            
            FVec3& getPosition();
            
            FVec3& getRotation();
            
            FVec3& getScale();
            
            void setUI(bool _ui){ m_isUI = _ui; }
            
            bool isUI(){ return m_isUI; }
            
            void setAABB(SVBoundBox& _aabb);
            
            SVBoundBox& getAABB();
            
            SVBoundBox& getAABBSW();
            //设置z顺序
            void setZOrder(s32 _zorder);
            
            inline cptr8 getType(){ return ntype.c_str(); }
            inline s32 getuid(){ return uid; }
            inline cptr8 getname(){return m_name.c_str();}
            inline s32 getZOrder(){ return m_iZOrder;}
            inline bool getcanSelect(){ return m_canSelect; }
            inline bool getbeSelect(){ return m_beSelect; }
            inline bool getcanProcEvent(){ return m_canProcEvent; }
            inline bool getvisible(){ return m_visible; }
            inline void setname(const char* _name){ m_name = _name; }
            inline void setvisible(bool _visible){ m_visible = _visible; }
            inline void setPeronID(s32 _personID){ m_personID = _personID;}
            inline s32 getPersonID(){ return m_personID; }
            
            //设置材质
            void setMtl(SVMtlCorePtr _mtl);
            //获取材质
            SVMtlCorePtr getMtl();
        protected:
            //更新
            virtual void update(f32 dt);
            //剔除
            virtual bool _clip();
            //渲染
            virtual void render();
            //
            SVString ntype;       //节点类型
            SVString m_name;
            s32 uid;             //唯一ID
            s32 m_personID;
            s32 m_iZOrder;
            bool m_canSelect;
            bool m_beSelect;
            bool m_canProcEvent;
            bool m_visible;
            bool m_dirty;
            RENDERSTREAMTYPE m_rsType;    //渲染流类型
            //
            FMat4 m_localMat;       //本地矩阵
            FMat4 m_absolutMat;     //绝对世界矩阵
            FMat4 m_iabsolutMat;    //逆绝对世界矩阵
            
            FVec3 m_postion;    //位置
            FVec3 m_rotation;   //度
            FVec3 m_scale;      //缩放
            
            SVBoundBox m_aabbBox;    //AABB包围盒
            SVBoundBox m_aabbBox_sw; //AABB世界包围盒
            bool m_drawBox;         //是否渲染包围盒
            
            SVMtlCorePtr m_pMtl;    //材质
            
            bool m_isUI;
            
        public:
            //节点模块
            void addChild(SVNodePtr node);
            
            void addChild(SVNodePtr node, s32 iZOrder);
            
            bool removeChild(SVNodePtr node);
            
            bool removeFromParent();
            
            bool hasChild(SVNodePtr node);
            
            void clearChild();
            
            SVNodePtr getNode(cptr8 _name);
            
            u32 getChildNum();
            
            SVNodePtr getChild(u32 _index);
            
        protected:
            //父节点
            SVNodePtr m_parent;
             //子节点池
            typedef SVArray<SVNodePtr> NODEPOOL;
            NODEPOOL m_childNodePool;
            //排序
            void _sort_child();
            bool m_needsort;
        };
        
    }//!namespace node
    
}//!namespace sv



#endif //SV_NODE_H
