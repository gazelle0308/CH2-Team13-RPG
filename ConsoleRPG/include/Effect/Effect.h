// Copyright 2026/07/30 JinHo

#pragma once

template<typename Entity>
class Effect {
 public:

     void EffectAType();
     void EffectBType();

     void 9::(int effect) {
         if (LeftTurn[effect] == 0) { return; }

         this->LeftTurn[effect] = this->LeftTurn[effect] - 1;

         if (LeftTurn[effect] == 0) {
             this->buff[effect] = false;
         }
     }

 private:
     Entity* entity = nullptr;

     int LeftTurn[] = {};

     boolonBuff[] = {};
};
