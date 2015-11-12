#ifndef NVIM_FILEIO_H
#define NVIM_FILEIO_H

#include "nvim/buffer_defs.h"
#include "nvim/os/os.h"

/* Values for readfile() flags */
#define READ_NEW        0x01    /* read a file into a new buffer */
#define READ_FILTER     0x02    /* read filter output */
#define READ_STDIN      0x04    /* read from stdin */
#define READ_BUFFER     0x08    /* read from curbuf (converting stdin) */
#define READ_DUMMY      0x10    /* reading into a dummy buffer */
#define READ_KEEP_UNDO  0x20    /* keep undo info*/

/*
 * Struct to save values in before executing autocommands for a buffer that is
 * not the current buffer.
 */
typedef struct {
  buf_T       *save_curbuf;     /* saved curbuf */
  int use_aucmd_win;            /* using aucmd_win */
  win_T       *save_curwin;     /* saved curwin */
  win_T       *new_curwin;      /* new curwin */
  buf_T       *new_curbuf;      /* new curbuf */
  char_u      *globaldir;       /* saved value of globaldir */
} aco_save_T;

#ifdef INCLUDE_GENERATED_DECLARATIONS
// Events for autocommands
# include "auevents_enum.generated.h"
# include "fileio.h.generated.h"
#endif

/// Perform `code` with autocmds blocked.
///
/// @param code The code to block autocmds during
#define WITH_BLOCK_AUTOCMDS(code) \
  do {                            \
    block_autocmds();             \
    code;                         \
    unblock_autocmds();           \
  } while(0);

/// Perform `code` with autocmds possibly blocked.
///
/// @param block If true, block autocmds
/// @param code  The code to block autocmds during
#define WITH_MAYBE_BLOCK_AUTOCMDS(block, code) \
  do {                                         \
    bool _do_block = (block);                  \
    if (_do_block) {                           \
      block_autocmds();                        \
    }                                          \
    code;                                      \
    if (_do_block) {                           \
      unblock_autocmds();                      \
    }                                          \
  } while(0);

#endif  // NVIM_FILEIO_H
