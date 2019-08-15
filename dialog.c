#include "config.h"
#include <stdbool.h>
#include <unistd.h>
#include "dialog.h"
#include "curs_lib.h"
#include "mutt_curses.h"
#include "mutt_window.h"

void dialog_push(struct Dialog *dlg)
{
  if (!dlg || !MuttDialogWindow)
    return;

  struct MuttWindow *last = TAILQ_LAST(&MuttDialogWindow->children, MuttWindowList);
  if (last)
    last->state.visible = false;

  TAILQ_INSERT_TAIL(&MuttDialogWindow->children, dlg->root, entries);
  dlg->root->state.visible = true;
}

void dialog_pop(void)
{
  if (!MuttDialogWindow)
    return;

  struct MuttWindow *last = TAILQ_LAST(&MuttDialogWindow->children, MuttWindowList);
  if (!last)
    return;

  last->state.visible = false;
  TAILQ_REMOVE(&MuttDialogWindow->children, last, entries);

  last = TAILQ_LAST(&MuttDialogWindow->children, MuttWindowList);
  if (last)
    last->state.visible = true;
}
