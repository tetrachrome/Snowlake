/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2018 William Li

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#include "CmdlDriver.h"

#include "ArgumentParser.h"
#include "version.h"

// -----------------------------------------------------------------------------

CmdlDriver::CmdlDriver()
  : _opts()
{
}

// -----------------------------------------------------------------------------

const CmdlDriver::Options&
CmdlDriver::options() const
{
  return _opts;
}

// -----------------------------------------------------------------------------

bool
CmdlDriver::run(int argc, char** argv)
{
  ArgumentParser argparser(SNOWLAKE_PROG_NAME, SNOWLAKE_VERSION_STRING,
                           SNOWLAKE_PROG_DESC, SNOWLAKE_PROG_DESC_LONG);

  argparser.setUsageString(SNOWLAKE_PROG_USAGE);

  argparser.addStringParameter("output", 'o', "Output path", true,
                               &_opts.outputPath);
  argparser.addBooleanParameter("errors", 'e', "Treat warnings as errors",
                                false, &_opts.warningsAsErrors, false);
  argparser.addBooleanParameter("bail", 'b', "Bail on first error", false,
                                &_opts.bailOnFirstError, false);
  argparser.addBooleanParameter("debug", 'd', "Debug mode", false,
                                &_opts.debugMode, false);
  argparser.addBooleanParameter("verbose", 'v', "Verbose mode", false,
                                &_opts.verbose, false);
  argparser.addBooleanParameter("silent", 's', "Silent mode", false,
                                &_opts.silent, false);
  argparser.addBooleanParameter("no-annotation-comments", 'n',
                                "Suppress annotation comments", false,
                                &_opts.suppressAnnotationComments, false);
  argparser.setMinimumPositionalArgsRequired(1);

  const bool res = argparser.parseArgs(argc, argv);
  if (!res) {
    argparser.printHelp();
    return false;
  }

  _opts.inputPath = argparser.positionalArgs().front();

  return true;
}

// -----------------------------------------------------------------------------
