#pragma once

#include "IPlugEditorDelegate.h"

/**
 * @file
 * @copydoc IGEditorDelegate
 */

class IGraphics;
class IControl;

/** An editor delgate base class for a SOMETHING that uses IGraphics for it's UI */
class IGEditorDelegate : public IEditorDelegate
{
public:
  IGEditorDelegate(int nParams);
  ~IGEditorDelegate();

// IEditorDelegate
  void* OpenWindow(void* pHandle) override;
  void CloseWindow() override;
  virtual void SendControlValueFromDelegate(int controlTag, double normalizedValue) override;
  virtual void SendControlMsgFromDelegate(int controlTag, int messageTag, int dataSize = 0, const void* pData = nullptr) override;
  virtual void SendMidiMsgFromDelegate(const IMidiMsg& msg) override;
  void SendParameterValueFromDelegate(int paramIdx, double value, bool normalized) override;
  /** If you override this method you should call this parent, or implement the same functionality in order to get controls to update, when state is restored. */
  virtual void OnRestoreState() override;
  
  /** If you override this method you must call the parent! */
  virtual void OnUIOpen() override;

  //IGEditorDelegate
  /** Attach IGraphics context - only call this method if creating/populating your UI in your plug-in constructor.
   ** In that case do not override CreateGraphics()! */
  void AttachGraphics(IGraphics* pGraphics);
  
  /** Only override this method if you want to create IGraphics on demand (when UI window opens)! Implementation should return result of MakeGraphics() */
  virtual IGraphics* CreateGraphics() { return nullptr; }
  
  /** Only override this method if you want to create IGraphics on demand (when UI window opens), or layout controls differently for different UI sizes */
  virtual void LayoutUI(IGraphics* pGraphics) {};
  
  /** Get a pointer to the IGraphics context */
  IGraphics* GetUI() { return mGraphics; };
  
private:
  IGraphics* mGraphics = nullptr;
  bool mIGraphicsTransient = false; // If creating IGraphics on demand this will be true
};
