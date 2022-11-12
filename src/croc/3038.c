#include "common.h"
#include <libsnd.h>
#include <libcd.h>

#define FLAGS_PLAYERACTION_UNK02 0x00000002
#define FLAGS_PLAYERACTION_UNK04 0x00000004
#define FLAGS_PLAYERACTION_PLAYANIM 0x00000008
#define FLAGS_PLAYERACTION_HASSHADOW 0x00000020
#define FLAGS_PLAYERACTION_PAUSETRIGGERS 0x00000040
#define FLAGS_PLAYERACTION_HIDE 0x00080000
#define FLAGS_PLAYERACTION_CTRLSPEED 0x00200000
#define FLAGS_PLAYERACTION_PUSHABLE 0x01000000
#define FLAGS_PLAYERACTION_CTRLJUMP 0x02000000
#define FLAGS_PLAYERACTION_ATTACK 0x10000000
#define FLAGS_PLAYERACTION_COLLISIONOFF 0x40000000
#define FLAGS_PLAYERACTION_PUSHING 0x80000000

typedef struct {
    s16 a1, a2;
    s32 b, c, d, e, f;
} CamPos; /* size = 0x18 */

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} UnkStruct1;

typedef struct {
    /* 000 */ s8* data;
    /* 004 */ s32 unk4;
    /* 008 */ s32 unk8;
    /* 00C */ s32 unkC;
    /* 010 */ s32 unk10;
    /* 014 */ s32 unk14;
    /* 018 */ s32 unk18;
    /* 01C */ s32 unk1C;
    /* 020 */ s32 unk20;
    /* 024 */ s32 unk24;
    /* 028 */ s8 unk28[0x11C];
    /* 144 */ s32 unk144;
    /* 148 */ s32 unk148;
    /* 14C */ s32 unk14C;
    /* 150 */ s8 unk150[0x24];
    /* 174 */ s32 unk174;
    /* 178 */ s32 unk178;
    /* 17C */ s32 unk17C;
    /* 180 */ s32 unk180;
    /* 184 */ s32 unk184;
    /* 188 */ s32 unk188;
    /* 18C */ UnkStruct1* unk18C;
    /* 190 */ s32 unk190;
    /* 194 */ s32 unk194;
    /* 198 */ s8 unk198[0x1D0];
    /* 368 */ CamPos unk368;
    /* 380 */ s8 unk380[0x18];
    /* 398 */ CamPos unk398;
    /* 3B0 */ s8 unk3b0[0x24];
    /* 3D4 */ s32 shadowSize;
    /* 3D8 */ s8 shadowType;
} Strategy; /* size = ??? */

extern s32 CameraHold;
extern s32 CameraHeight;
extern s32 CameraDist;
extern s32 CameraDistUse;
extern Strategy* CameraLookAtStrat;
extern Strategy* CameraLookAtStrat2;
extern s32 GobboDir;
extern s32 GobboXPos;
extern s32 OldGobboCount;
extern s32 vb_timer;
extern s32 LevelReset;
extern s32 BonusDisplay;
extern void* CardDir;

void stCommandError(Strategy* st);
void stLoadObject(Strategy* st);
void stLoadSprite(Strategy* st);
void stLoadAnim(Strategy* st);
void stLoadSample(Strategy* st);
void stLoadAnimFlag(Strategy* st);
void stTurnTowardX(Strategy* st);
void stTurnTowardY(Strategy* st);
void stTurnTowardWaypointX(Strategy* st);
void stPlaySound(Strategy* st);
void stStopSound(Strategy* st);
void stPlayAnim(Strategy* st);
void stStopAnim(Strategy* st);
void stWaitAnimend(Strategy* st);
void stPrint(Strategy* st);
void stSpecialFXOn(Strategy* st);
void stWait(Strategy* st);
void stRepeat(Strategy* st);
void stUntil(Strategy* st);
void stWhile(Strategy* st);
void stEndWhile(Strategy* st);
void stIf(Strategy* st);
void stElse(Strategy* st);
void stIfAnimend(Strategy* st);
void stFor(Strategy* st);
void stNext(Strategy* st);
void stSwitch(Strategy* st);
void stEndCase(Strategy* st);
void stProcCall(Strategy* st);
void stResetPosition(Strategy* st);
void stGoto(Strategy* st);
void stScaleX(Strategy* st);
void stScaleY(Strategy* st);
void stScaleZ(Strategy* st);
void stJump(Strategy* st);
void stFall(Strategy* st);
void stMoveBackward(Strategy* st);
void stMoveForward(Strategy* st);
void stMoveRight(Strategy* st);
void stMoveDown(Strategy* st);
void stMoveLeft(Strategy* st);
void stMoveUp(Strategy* st);
void stTurnRight(Strategy* st);
void stTurnLeft(Strategy* st);
void stTiltBackward(Strategy* st);
void stTiltForward(Strategy* st);
void stTiltRight(Strategy* st);
void stTiltLeft(Strategy* st);
void stSpawn(Strategy* st);
void stCreateTrigger(Strategy* st);
void stKillTrigger(Strategy* st);
void stCommandError(Strategy* st);
void stEndTrigger(Strategy* st);
void stRemove(Strategy* st);
void stLetGVar(Strategy* st);
void stLetPGVar(Strategy* st);
void stLetAVar(Strategy* st);
void stEndProc(Strategy* st);
void stSetModel(Strategy* st);
void stFileEnd(Strategy* st);
void stBlink(Strategy* st);
void stHoldTrigger(Strategy* st);
void stReleaseTrigger(Strategy* st);
void stSetAnim(Strategy* st);
void stTurnTowardXY(Strategy* st);
void stCommandError(Strategy* st);
void stHold(Strategy* st);
void stRelease(Strategy* st);
void stInc(Strategy* st);
void stPlayerAttackOn(Strategy* st);
void stPlayerAttackOff(Strategy* st);
void stCamWobble(Strategy* st);
void stLookAtMe(Strategy* st);
void stShadowSize(Strategy* st);
void stShadowType(Strategy* st);
void stClearAnim(Strategy* st);
void stStopFall(Strategy* st);
void stSetPlayerPosRel(Strategy* st);
void stCollectKey(Strategy* st);
void stRemoveKey(Strategy* st);
void stCommandError(Strategy* st);
void stCommandError(Strategy* st);
void stCollisionOn(Strategy* st);
void stCollisionOff(Strategy* st);
void stPauseTriggers(Strategy* st);
void stUnpauseTriggers(Strategy* st);
void stSetPosition(Strategy* st);
void stIsPlayer(Strategy* st);
void stIfJumping(Strategy* st);
void stIfFalling(Strategy* st);
void stScale(Strategy* st);
void stTurnTowardWaypointY(Strategy* st);
void stHide(Strategy* st);

s32 getPCword(Strategy*);

void srand(unsigned int seed);
s32 rcos(s32);
s32 rsin(s32);
s32 stEvaluate(Strategy* st);
void CameraResetPos();
void AccPlatStuff(Strategy* st, s32 arg);
void InitStats();
void GetDirectory(void**);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", VBInt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", VBInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", main);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadPad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", xinit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", xalloc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", xcurrent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", xfree);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", xreset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cxalloc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cxcurrent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cxfree);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cxreset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawSetProjection);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawAllocateBuffers);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawNextPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawAddPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawSetLight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawSetWLight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawRotLight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawRotLightScale);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawUnitSetup);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawUnitSetupFont);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawCamera);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawCameraLookAt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawTranslate);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawRotate);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawMatrixS);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawStart);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawEnd);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ScreenBCol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReorgScreen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ScreenInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ScreenClear);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ScreenSwap);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ScreenSwapVB);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ScreenLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ClearVram);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetDist);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestPos);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestPos2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelLight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestLight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelRelight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelMapLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelMapLoadMany);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectDrawX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TrackDrawRTLX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawSpriteX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawShadowsX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawSpritesX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawAnimStrat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SubdivideGT4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SubdivideGT3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SubdivideG4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SubdivideG3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TrackDrawX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MapDraw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ColourAdd);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MapPrepare);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", BackDrawX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", BackPrepare);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AnimLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Anim2Open);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Anim2Close);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Anim2Frame);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCReadyCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCDataCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCGameState);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCOpen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCOpenXA);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCClose);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCRead);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCSkip);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", hang);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCExists);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MakeDirectoryQuickTable);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCDoPreSeek);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCSetUpPreSeek);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FCPreSeek);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadLittleMaps);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MapLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FindFirstDoor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FindLinkedDoor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EnemyTextureLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", IntroTextureLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", BackGroundTextureLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MapTextureLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextureLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoAnimTextures);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoColourCycle);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ClearCycleInfo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Reset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", QuickReset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stInitStrategyCode);

void push_stack(s8* data);
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", push_stack);

s8* pop_stack();
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", pop_stack);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stAddStrategy);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRemoveStrategy);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCollisionOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCollisionOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetCollPoint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetCollPoints);

void stPlayerCollisionOn(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_COLLISIONOFF;
}

void stPlayerCollisionOff(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_COLLISIONOFF;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stActivated);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stUnActivated);

void stCollected(Strategy* arg0) {
    arg0->data++;
    if (arg0->unk18C) {
        arg0->unk18C->unk14 |= 4;
    }
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlayerNoStood);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRemoveFromMap);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRemoveModel);

void stRemove(Strategy* st) {
    st->unk174 |= FLAGS_PLAYERACTION_UNK02 | FLAGS_PLAYERACTION_UNK04;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRelease);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stHold);

void stLoadObject(Strategy* st) { st->data++; }

void stLoadSample(Strategy* st) { st->data++; }

void stLoadAnim(Strategy* st) { st->data++; }

void stLoadAnimFlag(Strategy* st) { st->data++; }

void stLoadSprite(Strategy* st) { st->data++; }

void stHide(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_HIDE;
}

void stUnhide(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_HIDE;
}

void stNoHang(Strategy* st) {
    st->data++;
    st->unk178 |= 0x100;
}

void stOpenEyes(Strategy* st) {
    st->data++;
    st->unk17C = 0;
}

void stLineNumber(Strategy* st) { st->data += 3; }

void stHeightFloat(Strategy* st) {
    st->data++;
    st->unk14C = 699;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCloseEyes);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stBlink);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stWobble);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLoopSound);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetEnvelope);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPitchShift);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlaySound);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stStopSound);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlayAnim);

void stClearAnim(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_PLAYANIM;
    st->unk24 = 0;
}

void stStopAnim(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_PLAYANIM;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stWaitAnimend);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stIfJumping);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stIfFalling);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stIfAnimend);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPrint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stWait);

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRepeat);
#else
void stRepeat(Strategy* st) { push_stack(st->data++); }
#endif

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stUntil);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stUntilImm);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stWhile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stEndWhile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stEndWhileImm);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stIf);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stElse);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stFor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stNextImm);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stNext);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSwitch);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stEndCase);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stScale);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stScaleX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stScaleY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stScaleZ);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stJump);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stStomp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stFloat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stStopFall);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stFall);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveBackward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stBonus);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMovePlayerForward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMovePlayerBackward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetPlayerPosRel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveForwardAngle);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveForward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveRight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveLeft);

void stSpecialFXOn(Strategy* st) {
    st->data++;
    stEvaluate(st);
}

void stSpecialFXOff(Strategy* st) {
    st->data++;
    stEvaluate(st);
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveUp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMoveDown);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardPlayerX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardPlayerY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardPlayerXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardPosX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardPosY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardPosXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardWaypointX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardWaypointY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnTowardWaypointXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnRight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTurnLeft);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTiltBackward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTiltForward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTiltRight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stTiltLeft);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSpawnFrom);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSpawnChild);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSpawn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCreateTrigger);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stKillTrigger);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stHoldTrigger);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stReleaseTrigger);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stEndTrigger);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stUserTrigger);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCommandError);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLetPGVar);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLetGVar);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLetXGVar);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLetParam);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLetXParam);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stWaitEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLetAVar);

void stEndProc(Strategy* st) { st->data = pop_stack(); }

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stProcCall);
#else
void stProcCall(Strategy* st) {
    u8* stack = st->data;
    st->data++;
    push_stack(stack + 3);
    st->data = getPCword(st) + st->unk4;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stGoto);
#else
void stGoto(Strategy* st) {
    st->data++;
    st->data = getPCword(st) + st->unk4;
    st->unk174 |= 2;
}
#endif

void stPauseTriggers(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_PAUSETRIGGERS;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPauseTriggersNoAnim);

void stUnpauseTriggers(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_PAUSETRIGGERS;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetModel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPausePlayer);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stUnpausePlayer);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stForceDoor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetAnimSpeed);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetAnim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stFileEnd);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stQuickPlayer);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stIsPlayer);

void stReSeed(Strategy* st) {
    st->data++;
    srand(vb_timer);
}

void MarkLevelComplete();
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MarkLevelComplete);

void stEndLevel(Strategy* st) {
    st->data++;
    MarkLevelComplete();
    LevelReset = 4;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CheckForSecret);

void stNextLevel(Strategy* st);
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stNextLevel);

void stEndSubLevel(Strategy* st) {
    InitStats();
    stNextLevel(st);
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stSetLevel);

void stPushCamera(Strategy* st) { st->data++; }

void stPullCamera(Strategy* st) { st->data++; }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stNearestWaypointNext);

void stNearestWaypointPrev(Strategy* st) { st->data++; }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPushWaypoint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPullWaypoint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stDeleteWaypoint);

void stFirstWaypoint(Strategy* st) {
    st->data++;
    st->unk190 = st->unk194;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stNextWaypoint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPrevWaypoint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AccPlatStuff);

void stSpeedUp(Strategy* st) {
    st->data++;
    AccPlatStuff(st, stEvaluate(st));
}

void stSmoothSpeed(Strategy* st) {
    st->data++;
    AccPlatStuff(st, stEvaluate(st));
}

void stSlowDown(Strategy* st) {
    st->data++;
    stEvaluate(st);
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stInc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stDec);

void stLookAtMe(Strategy* st) {
    st->data++;
    CameraLookAtStrat = st;
    CameraResetPos();
}

void stLookAtMe2(Strategy* st) {
    st->data++;
    CameraLookAtStrat2 = st;
}

void stTurnOffLookAtMe2(Strategy* st) {
    st->data++;
    CameraLookAtStrat2 = 0;
}

void stLookAtMeMap(Strategy* st) {
    st->data++;
    CameraLookAtStrat = st;
}

void stVibrate(Strategy* st) {
    st->data++;
    stEvaluate(st);
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCamWobble);

void stCamHold(Strategy* st) {
    st->data++;
    CameraHold = stEvaluate(st) >> 0x10;
}

void stSetCamHeight(Strategy* st) {
    st->data++;
    CameraHeight = stEvaluate(st) >> 4;
}

void stSetCamDist(Strategy* st) {
    st->data++;
    CameraDistUse = CameraDist = stEvaluate(st) >> 4;
}

void stSetPosition(Strategy* st) {
    st->data++;
    st->unk398 = st->unk368;
}

void stResetPosition(Strategy* st) {
    st->data++;
    st->unk368 = st->unk398;
}

void stJumpCtrlOn(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_CTRLJUMP;
}

void stJumpCtrlOff(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_CTRLJUMP;
}

void stPlayerAttackOn(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_ATTACK;
}

void stPlayerAttackOff(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_ATTACK;
}

void stAnimCtrlSpdOn(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_CTRLSPEED;
}

void stAnimCtrlSpdOff(Strategy* st) {
    st->data++;
    st->unk174 &= 0xFFDFFFFF;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlayerDead);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRemoveGobbo);

void stGobboON(Strategy* st) {
    st->data++;
    GobboXPos = 390;
    GobboDir = 0;
    OldGobboCount = -1;
}

void stGobboOFF(Strategy* st) {
    st->data++;
    GobboXPos = 600;
    GobboDir = -1;
}

void stSetCamera(Strategy* st) {
    st->data++;
    stEvaluate(st);
}

void stShadowOn(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_HASSHADOW;
}

void stShadowOff(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_HASSHADOW;
}

void stShadowSize(Strategy* st) {
    st->data++;
    st->shadowSize = stEvaluate(st);
}

void stShadowType(Strategy* st) {
    st->data++;
    st->shadowType = *st->data++;
}

void stPushingOn(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_PUSHING;
}

void stPushingOff(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_PUSHING;
}

void stSlideOn(Strategy* st) {
    st->data++;
    st->unk178 |= 1;
}

void stSlideOff(Strategy* st) {
    st->data++;
    st->unk178 &= ~1;
}

void stPushableOn(Strategy* st) {
    st->data++;
    st->unk174 |= FLAGS_PLAYERACTION_PUSHABLE;
}

void stPushableOff(Strategy* st) {
    st->data++;
    st->unk174 &= ~FLAGS_PLAYERACTION_PUSHABLE;
}

void stHangOn(Strategy* st) {
    st->data++;
    st->unk178 |= 0x1000;
}

void stHangOff(Strategy* st) {
    st->data++;
    st->unk178 &= ~0x1000;
}

void stFlashOn(Strategy* st) { st->data++; }

void stFlashOff(Strategy* st) { st->data++; }

void MoveStratForwardAngle(Strategy* st, s32 arg1, s32 angle) {
    st->unk368.c += (arg1 * rsin(angle)) >> 0xC;
    st->unk368.e += (arg1 * rcos(angle)) >> 0xC;
}

void MoveStratForward(Strategy* st, s32 arg1) {
    st->unk368.c += (arg1 * rsin(st->unk368.a2)) >> 0xC;
    st->unk368.e += (arg1 * rcos(st->unk368.a2)) >> 0xC;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stMovePosition);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stProcessStrategies);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stDrawStrategies);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stResolveReferences);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StratCollision);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StDoFall);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StDoJump);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SearchForEntry);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stResetStrats);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetSoundSystem);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitSpu);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadReverb);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitSnd);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SoundInitialise);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ShutdownSpu);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ShutdownSnd);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SoundShutdown);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SoundFadeUp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SoundFadeDown);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SoundPause);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SoundResume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetCommonAttr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitReverb);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXReverbOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXReverbOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoSpatialPositioning);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXVolumeCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXPitchChange);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", HasSFXfinished);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXStop);

void SFXStopAll(s32);
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXStopAll);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXPause);

void SFXResume(void) {}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXSetVolume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXChangeVolume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXSetEnvelope);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SFXSetSpeakerMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stEvaluate);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CheckTrackFloor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CheckTrackCeiling);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CheckStrat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionTrackX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionTrack);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionWallX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionWall);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionWallCamera);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionWallCameraZoom);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionPosition);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionPosition2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionDist);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionDistNoY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectDistV);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionPlayerDist);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CollisionPlayer);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraDistAng);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraDistAng2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraTarget);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraOffsetTarget);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectDist);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", WithinDist);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectAng);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectAngXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectDistNoY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AnalogueSetup);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DecodePad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitFont);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetMapName);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitMapStuff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LevelName);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitCard);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestCard);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_event);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _clear_event);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_event_x);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _clear_event_x);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetDirectory);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FormatCard);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DeleteFile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetPercent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SaveGame);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadGame);

void ReadDir(void) { GetDirectory(&CardDir); }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetGame);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetGameFromContinue);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadHeader);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestFormat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SaveOptions);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetupBackground);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", IntroBackground);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoBackground);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadCredits);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitCredits);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoCredits);

void SaveCrocPosition(void) {}

void LoadCrocPosition(void) {}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoDoor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", IsOkayToPause);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", IsFadeComplete);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoFades);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EndFade);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", HoldEndFade);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitForeground);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Fade2Black);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Fade2BlackNoMusic);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Fade2HalfBlack);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FadeinFromBlack);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FadeinFromBlackNoMusic);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Fade2White);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Fade2WhiteQuick);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FadeinFromWhite);

void DoWipeRotate();
INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoWipeRotate);

void WipeRotateNoMusicFade(void) { DoWipeRotate(); }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", WipeRotate);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitFade);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FlatPolyLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PreLoadFades);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoHalfFade);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StartDefaultMapStrategies);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SolveAllStrats);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AddAllStrats);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PreLoadSFX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PreLoadModel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PreLoadStrats);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadMapWad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SolveMem);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SolveStrat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SolveMemContig);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SolveStratContig);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraTransLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraGameInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraResetPos);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraGameStrategy);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraMapInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraMapStrategy);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraTitleInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CameraTitleStrategy);

void stTonyTest(Strategy* st) { st->data++; }

void stLewisTest(Strategy* st) {
    st->data += 2;
    stEvaluate(st);
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PlayerMoveReset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stDecelerateAngle);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stAccelerateAngle);

void stDecelerate(Strategy* st) { st->data++; }

void stReverse(Strategy* st) { st->data++; }

void stAccelerate(Strategy* st) { st->data++; }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stStopDead);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlayerMoveInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlayerMove);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stPlayerTurn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCollectKey);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRemoveKey);

void stShowBonus(Strategy* st) {
    st->data++;
    BonusDisplay = 60;
}

void stShowBonusOn(Strategy* st) {
    st->data++;
    BonusDisplay = -1;
}

void stShowBonusOff(Strategy* st) {
    st->data++;
    BonusDisplay = 0;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stAddPickup);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stLosePickups);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stInitCrystal);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCrystal);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stEndCrystal);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stRemoveCrystal);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCollectJigsaw);

void stLevelStats(Strategy* st) {
    st->data++;
    InitStats();
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadAmbient);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SEQLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SEQPlay);

void SEQPause(void) { SsSeqStop(0); }

void SEQResume(void) { SsSeqPlay(0, 1, 0); }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SEQFadeUp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SEQFadeOut);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SEQHalveVolume);

void SEQStop(void) {
    SFXStopAll(1);
    SsVabClose(0);
    SsSeqClose(0);
    SsEnd();
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitPanel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPanel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoPanel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTexture);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTextureIcon);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitTextList);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetTextWidth);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetLikkleTextWidth);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrint);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintBack);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintBig);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetBigWidth);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintPanelXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintPanel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintWithoutWidth);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintCoords);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintSizeXY);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintSize);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintIcon);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintLikkleSize);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintSizePanel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitBanner);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoBanner);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitTitleLogo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AddSparkle);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoTitleLogo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoLogo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TextPrintLoader);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", QuikCount);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoSecretCheck);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoShade);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Init8x8Screen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Init16x16Screen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Display8x8Screen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Display16x16Screen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Display8x8ScreenWipe0);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitRain);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitSnow);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitSpecialEffect);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpecialEffectsDriver);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stCreateDeath);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stDoDeath);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PreModel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadOptions);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadLevel);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestCardFormat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OpDoXTri);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OpDoX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OpDoTri);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OpDoLRTri);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitOptions);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoOptions);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitLoadSaveMenu);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AnimateIcons);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DownloadIcon);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DownloadBlank);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Display);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoLoadSaveMenu);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadDefault);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MakeDefault);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DefaultOptions);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ObjectDraw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TrackDrawRTL);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawSprite);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawShadows);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ModelDrawSprites);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TrackDraw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", BackDraw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", IntroPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDSetMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDVSyncCommand);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDInitialise);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadMusicMap);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDShutdown);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDReset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetFilter);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDPause);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDResume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDStop);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDFadeOutNoSeek);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDChangeVolume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDSetVolume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDFadeIn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDFadeOut);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDLongFadeOut);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CheckMusic);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDSkipForward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDSkipBackward);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDGetTimeElapsed);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDcbReady);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDLoopcbReady);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CDBeginPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PasswordInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GivePassword);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EnterPassword);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Adjust);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", HandleMenus);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitMenu);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitLoader);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", VBLoading);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StartLoader);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EndLoader);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitStats);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoNumber);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DoLevelStats);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LevelStatsFinished);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", getPClong);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", getPCword);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", rsin);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", sin_1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", rcos);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", func_8005402C);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitGeom);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SquareRoot12);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MulMatrix0);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ApplyMatrixLV);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ApplyRotMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PushMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PopMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadRotMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MulMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MulMatrix2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ApplyMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TransMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetRotMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetColorMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTransMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetBackColor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetFarColor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetGeomOffset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetGeomScreen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LightColor);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DpqColorLight);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DpqColor3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Intpl);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Square12);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Square0);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AverageZ3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AverageZ4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OuterProduct12);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OuterProduct0);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Lzc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TransposeMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", RotMatrix);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", RotMatrixYXZ);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ratan2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _patch_gte);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadTPage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadClut);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadClut2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDefDrawEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDefDispEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetTPage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetClut);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DumpTPage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DumpClut);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", NextPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", IsEndPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AddPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", AddPrims);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CatPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TermPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetSemiTrans);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetShadeTex);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyF3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyFT3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyG3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyGT3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyF4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyFT4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyG4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPolyGT4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetSprt8);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetSprt16);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetSprt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTile1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTile8);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTile16);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetLineF2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetLineG2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetLineF3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetLineG3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetLineF4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetLineG4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawTPage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawMove);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawLoad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MargePrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DumpDrawEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DumpDispEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetGraph);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetGraphReverse);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetGraphDebug);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetGraphQueue);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetGraphType);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetGraphDebug);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawSyncCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDispMask);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", checkRECT);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ClearImage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ClearImage2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", LoadImage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StoreImage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", MoveImage);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ClearOTag);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ClearOTagR);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawPrim);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawOTag);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PutDrawEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DrawOTagEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetDrawEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PutDispEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetDispEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetODE);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetTexWindow);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawArea);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawOffset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPriority);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetDrawEnv2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_mode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_cs);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_ce);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_ofs);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_tw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_dx);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _status);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _otc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _clr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _dws);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _drs);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _ctl);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _getctl);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _cwb);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _cwc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _param);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _addque);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _addque2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _exeque);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _reset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _sync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", set_alarm);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", get_alarm);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _version);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", VSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", v_wait);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InterruptCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DMACallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", VSyncCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", VSyncCallbacks);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StopCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", RestartCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CheckCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetIntrMask);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetIntrMask);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", startIntr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", trapIntr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", setIntr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", stopIntr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", restartIntr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memclr_1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", startIntrVSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", trapIntrVSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", setIntrVSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memclr_2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", startIntrDMA);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", trapIntrDMA);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", setIntrDMA);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memclr_3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetVideoMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetVideoMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", FlushCache);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GPU_cw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _96_remove);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", OpenEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", TestEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EnableEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReturnFromException);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetEntryInt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", HookEntryInt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EnterCriticalSection);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ExitCriticalSection);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetSp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", open);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", lseek);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", read);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", write);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", close);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", format);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", firstfile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", nextfile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", erase);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ChangeClearPAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ChangeClearRCnt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetInitPadFlag);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ReadInitPadFlag);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PAD_init);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitPAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StartPAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StopPAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetPatchPad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", RemovePatchPad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _Pad1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _IsVSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitPAD2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StartPAD2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StopPAD2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", PAD_init2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SysEnqIntRP);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SysDeqIntRP);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", EnablePAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DisablePAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _patch_pad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SendPAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _send_pad);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _remove_ChgclrPAD);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", __SN_ENTRY_POINT);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", __main);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", __do_global_dtors);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", InitHeap);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", puts);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", setjmp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", strcat);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", strcmp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", strncmp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", strcpy);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", strlen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", strrchr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memcpy);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", rand);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", srand);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", printf);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", sprintf);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memchr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", memmove);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsClose);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqClose);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSepClose);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsEnd);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqOpen);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContBankChange);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContDataEntry);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContMainVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContPanpot);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContExpression);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContDamper);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContExternal);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContNrpn1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContNrpn2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContRpn1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContRpn2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsContResetAll);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr0);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr1);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr4);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsUtResolveADSR);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsUtBuildADSR);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr5);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr6);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr7);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr8);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr9);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr10);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr11);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr12);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr13);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr14);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr15);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr16);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr17);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr18);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetNrpnVabAttr19);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetPitchBend);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetControlChange);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsGetMetaEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsNoteOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSetProgramChange);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsReadDeltaValue);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsInitSoundSeq);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSepPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsQuit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", Snd_SetPlayMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsStart);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsStart);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsStart2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsTrapIntrVSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSeqCalledTbyT_1per2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SetRCnt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", GetRCnt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StartRCnt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", StopRCnt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", ResetRCnt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqCalledTbyT);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndCrescendo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndDecrescendo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndPause);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSeqPlay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSeqGetEof);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsGetSeqData);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndNextSep);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndReplay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndStop);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqStop);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSepStop);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSetTableSize);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSetTickMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndSetVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqSetVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSepSetVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSeqGetVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsSndTempo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtFlush);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtGetProgAtr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtGetVagAtr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtKeyOnV);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtKeyOffV);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtSetReverbDelay);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtSetReverbDepth);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtSetReverbType);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtGetReverbType);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtSetReverbFeedback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtReverbOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtReverbOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsUtSetVagAtr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmDoAllocate);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmDamperOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmDamperOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmFlush);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmKeyOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmKeyOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSeKeyOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSeKeyOff);

void KeyOnCheck(void) {}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmAlloc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", note2pitch);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", note2pitch2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", vmNoiseOn);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", vmNoiseOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmKeyOffNow);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmKeyOnNow);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmPBVoice);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmPitchBend);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSetProgVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmGetProgVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSetProgPan);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmGetProgPan);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSetSeqVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmGetSeqVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmGetSeqLVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmGetSeqRVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSeqKeyOff);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSelectToneAndVag);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmSetVol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SsVmVSetUp);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSetMono);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSetStereo);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsSetReservedVoice);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabClose);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabOpenHead);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabOpenHeadSticky);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabFakeHead);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabOpenHeadWithMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabTransBody);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SsVabTransCompleted);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuStart);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_init);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FwriteByIO);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FiDMA);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_Fr_);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_t);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_Fw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_Fr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FsetRXX);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FsetRXXa);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FgetRXXa);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FsetPCR);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FsetDelayW);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_FsetDelayR);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_Fw1ts);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DeliverEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuDataCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuQuit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CloseEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", DisableEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuInitMalloc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuMalloc);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_gcSPU);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuMallocSeparateTo3);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuMallocWithStartAddr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuFree);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetEnv);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetVoiceAttr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetNoiseVoice);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuSetAnyVoice);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetReverb);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuIsInAllocateArea);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuIsInAllocateArea_);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetReverbModeParam);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_setReverbAttr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuReserveReverbWorkArea);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetReverbDepth);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetReverbVoice);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuClearReverbWorkArea);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", WaitEvent);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetKey);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuGetKeyStatus);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetKeyOnWithAttr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuWrite);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetTransferStartAddr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetTransferMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuIsTransferCompleted);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_setInTransfer);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_getInTransfer);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetCommonAttr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _SpuRSetVoiceAttr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_2pitch);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_note2pitch);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _spu_pitch2note);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetVoiceVolume);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuSetVoicePitch);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", SpuGetVoicePitch);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_info);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_load);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_read);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_clear);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _card_write);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", _new_card);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdInit);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", def_cbsync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", def_cbready);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", def_cbread);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdStatus);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdMode);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdLastCom);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdLastPos);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReset);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdFlush);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdSetDebug);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdComstr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdIntstr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReady);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdSyncCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReadyCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdControl);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdControlF);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdControlB);

void CD_vol(CdlATV* vol);
s32 CdMix(CdlATV* vol) {
    CD_vol(vol);
    return 1;
}

s32 CD_getsector(void* madr, s32 size);
s32 CdGetSector(void* madr, s32 size) { return CD_getsector(madr, size) == 0; }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdGetSector2);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdDataCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdDataSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdIntToPos);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdPosToInt);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", getintr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_sync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_ready);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_cw);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_vol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_flush);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_initvol);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_initintr);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_init);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_datasync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_getsector);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_getsector2);

extern s32 D_80073A98;
void CD_set_test_parmnum(s32 arg0) { D_80073A98 = arg0; }

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", callback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdSearchFile);

s32 _cmp(const char* str1, const char* str2) {
    return strncmp(str1, str2, 12) == 0;
}

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_newmedia);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_searchdir);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CD_cachefile);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cd_read);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cb_read);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cb_data);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", cd_read_retry);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReadBreak);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdRead);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReadSync);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReadCallback);

INCLUDE_ASM("config/../asm/croc/nonmatchings/3038", CdReadMode);
