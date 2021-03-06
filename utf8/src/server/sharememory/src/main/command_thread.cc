#include "server/share_memory/main/command_thread.h"
#include "server/common/base/log.h"

CommandThread g_command_thread;

CommandThread::CommandThread() {
  __ENTER_FUNCTION
    active_ = true;
  __LEAVE_FUNCTION
}

CommandThread::~CommandThread() {
  //do nothing
}

void CommandThread::run() {
  __ENTER_FUNCTION
    while (is_active()) {
      bool result = false;
      result = CommandParser::handleinput();
      Assert(result);
    }
  __LEAVE_FUNCTION
}


bool CommandParser::handleinput() {
  __ENTER_FUNCTION
    bool result = true;
    char cmd[kCmdSize];
    memset(cmd, '\0', sizeof(cmd));
    uint32_t charcount = 0;
    int32_t charinput;
    for(;;) {
      charinput = getchar();
      if ('\n' == charinput) break;
      if (charcount > sizeof(cmd) - 1) break;
      cmd[charcount] = static_cast<char>(charinput);
      ++charcount;
    }
    command_state_t state = parser_commandtype(cmd);
    switch (state.type) {
      case kCmdSaveAll: {
        g_command_thread.command_config.state = state;
        g_log->fast_save_log(kShareMemoryLogFile, "start save all%s", LF);
      }
      case kCmdClearAll: {
        g_command_thread.command_config.state = state;
        g_log->fast_save_log(kShareMemoryLogFile, "start clear all%s", LF); 
      }
      default: {
        g_log->fast_save_log(kShareMemoryLogFile, "unkown command%s", LF);
      }
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

command_state_t CommandParser::parser_commandtype(const char* str) {
    command_state_t state;
    state.type = kCmdUnkown;
  __ENTER_FUNCTION
    char cmdhead[kCmdSize];
    memset(cmdhead, '\0', sizeof(cmdhead));
    uint32_t i;
    for (i = 0; i < sizeof(cmdhead) - 1; ++i) {
      char charinput = str[i];
      if (' ' == charinput || '\t' == charinput || '\0' == charinput) break;
      cmdhead[i] = str[i];
    }
    if (0 == strcmp(cmdhead, "saveall")) {
      state.type = kCmdSaveAll;
    }
    else if (0 == strcmp(cmdhead, "clearall")) {
      state.type = kCmdClearAll;
    }
    return state;
  __LEAVE_FUNCTION
    return state;
}

bool CommandThread::is_active() {
  __ENTER_FUNCTION
    return active_;
  __LEAVE_FUNCTION
    return false;
}

void CommandThread::stop() {
  __ENTER_FUNCTION
    active_ = false;
  __LEAVE_FUNCTION
}
