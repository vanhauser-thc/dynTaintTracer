#include "idc.idc"

static string2long(str) {
  auto result, tmp, minus;

  result = strstr(str, "0x");
  if (result != -1) {
    result = xtol(str);
  } else {
    result = atol(str);
  }
  //Message("Debug: str \"%s\" ? minus %d = %ld | 0x%lx ; %ld\n", str, minus, result, result, 5 - 8);

  return result;
}

static main() {
  auto a, b, bb, f, l, first, last;

  Wait();

  a = AskFile(0, "*.*", "Enter the file to read in");
  if (a == "") {
    Message("Aborted by user\n");
    return;
  }
  f = fopen(a, "r");
  if (!f) {
    Message("Error: file %s not found\n", a);
    return;
  }

  bb = ask_str("0", 0, "Enter an offset for the addresses to add (or subtract if minus) if required (preceed hex value with 0x) [common: -0x555555554000]");
  b = string2long(bb);
  if (b == -1) {
    Message("Aborted by user\n");
    return;
  }
  Message("Offset: 0x%lx/%ld\n", b, b);
  first = 0; last = 0;

  l = readstr(f);
  while(l != -1) {
    auto from, to, split, fromval, toval, ending, str, old, ok;
    fromval = 0;
    //Message("Line: %s\n", l);
    // INDIRECT call from 0x12345678 to 0x00abcdef
    if (strstr(l, "INDIRECT ") != -1 && (from = strstr(l, " from ")) != -1 && (split = strstr(l, " to ")) != -1) {
      from = from + 6;
      to = split + 4;
      fromval = xtol(substr(l, from, split)) + b;
      toval = xtol(substr(l, to, -1)) + b;
      Message("Indirect call/jmp from 0x%lx to 0x%lx\n", fromval, toval);
      AddCodeXref(fromval, toval, fl_CF | XREF_USER);
      old = Comment(fromval);
      if (old == -1 || strlen(old) == 0) {
        str = form("Xref: 0x%lx", toval);
      } else {
        str = form("%s, 0x%lx", old, toval);
      }
      MakeComm(fromval, str);
      old = Comment(toval);
      if (old == -1 || strlen(old) == 0) {
        str = form("XrefFrom: 0x%lx", fromval);
      } else {
        str = form("%s, 0x%lx", old, fromval);
      }
      MakeComm(toval, str);
      SetColor(fromval, CIC_ITEM, 0xee00ee); // pink
      SetColor(toval, CIC_ITEM, 0xee00ee);   // pink
    }
    // TAINT 0x12345678 mov eax, [ebx + 3] ; ebx:8
    if (strstr(l, "TAINT ") != -1 && strstr(l, "UNTAINT ") == -1) {
      from = strstr(l, " ");
      from = from + 1;
      fromval = xtol(substr(l, from, -1)) + b;
      to = strstr(l, ";");
      if (SetColor(fromval, CIC_ITEM, 0xffbbff) != 0) { // plum
        if (to != BADADDR) {
          to = to + 2;
          ending = strstr(l, "\r");
          if (ending == -1) {
            ending = strstr(l, "\n");
          }
          if (ending == -1) {
            str = substr(l, to, -1);
          } else {
            str = substr(l, to, ending);
          }
          if (strlen(str) > 1)
            MakeComm(fromval, str);
        }
      }
      if (first == 0 && fromval != 0) {
        first = fromval;
        old = 1;
        while (GetMarkedPos(old) != -1)
          old++;
        MarkPosition(first, 0, 0, 0, old, "TAINT START");
      }
      if (fromval != 0)
        last = fromval;
      Message("Tainting 0x%lx\n", fromval);
    }
    // MARK 0x12345678 ; comment and mark description
    if (strstr(l, "MARK ") != -1) {
      from = strstr(l, " ");
      from = from + 1;
      to = strstr(l, ";");
      fromval = xtol(substr(l, from, to)) + b;
      if (SetColor(fromval, CIC_ITEM, 0xeeeeee) != 0) { // very light grey
        if (to != BADADDR) {
          to = to + 2;
          ending = strstr(l, "\r");
          if (ending == -1) {
            ending = strstr(l, "\n");
          }
          if (ending == -1) {
            str = substr(l, to, -1);
          } else {
            str = substr(l, to, ending);
          }
          old = 1;
          while (GetMarkedPos(old) != -1)
            old++;
          ok = 1;
          if (strlen(str) > 1) {
            MakeComm(fromval, str);
          } else {
            str = ltoa(old, 10);
          } 
          MarkPosition(fromval, 0, 0, 0, old, str);
        }
      } 
      Message("Marked 0x%lx\n", fromval);
    }
    // PROBLEM 0x12345678 ; comment and description
    if (strstr(l, "PROBLEM 0x") != -1) {
      from = strstr(l, " ");
      from = from + 1;
      to = strstr(l, ";");
      fromval = xtol(substr(l, from, to)) + b;
      if (SetColor(fromval, CIC_ITEM, 0xee0000) != 0) { // light red
        if (to != BADADDR) {
          to = to + 2;
            ending = strstr(l, "\r");
            if (ending == -1) {
              ending = strstr(l, "\n");
          }
          if (ending == -1) {
            str = substr(l, to, -1);
          } else {
            str = substr(l, to, ending);
          }
          if (strlen(str) > 1)
            MakeComm(fromval, str);
        }
      }
      Message("Problem marker at 0x%lx\n", fromval);
    }
    // BB 0x12345678 ; comment and description
    if (strstr(l, "BB 0x") != -1) {
      from = strstr(l, " ");
      from = from + 1;
      to = strstr(l, ";");
      fromval = xtol(substr(l, from, to)) + b;
      if (GetColor(fromval, CIC_ITEM) != 0xffffff) { // only colour if not already coloured!
        if (SetColor(fromval, CIC_ITEM, 0xffe1ff) != 0) { // light violet
          if (to != BADADDR) {
            to = to + 2;
            ending = strstr(l, "\r");
            if (ending == -1) {
              ending = strstr(l, "\n");
            }
            if (ending == -1) {
              str = substr(l, to, -1);
            } else {
              str = substr(l, to, ending);
            }
            if (strlen(str) > 1)
              MakeComm(fromval, str);
          }
        }
      }
      Message("Basic Block at 0x%lx\n", fromval);
    }
    // COLOUR 0x12345678 ; comment and description
    if (strstr(l, "COLOR 0x") != -1 || strstr(l, "COLOUR 0x") != -1 || strstr(l, "UNTAINT 0x") != -1) {
      from = strstr(l, " ");
      from = from + 1;
      to = strstr(l, ";");
      fromval = xtol(substr(l, from, to)) + b;
      if (GetColor(fromval, CIC_ITEM) != 0xffffff) { // only colour if not already coloured!
        if (SetColor(fromval, CIC_ITEM, 0xbbbbbb) != 0) { // medium grey
          if (to != BADADDR) {
            to = to + 2;
            ending = strstr(l, "\r");
            if (ending == -1) {
              ending = strstr(l, "\n");
            }
            if (ending == -1) {
              str = substr(l, to, -1);
            } else {
              str = substr(l, to, ending);
            }
            if (strlen(str) > 1)
              MakeComm(fromval, str);
          }
        }
      }
      Message("Coloring 0x%lx\n", fromval);
    }

    l = readstr(f);
  }
  fclose(f);
  if (first != 0)
    Message("0x%lx: TAINT START\n", first);
  if (last != 0) {
    Message("0x%lx: TAINT END\n", last);
    old = 1;
    while (GetMarkedPos(old) != -1)
      old++;
    MarkPosition(last, 0, 0, 0, old, "TAINT END");
  }
}
