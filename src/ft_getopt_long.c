#include <stdio.h>
#include <string.h>

#include "ft_getopt_long.h"
#include "utils.h"

char *ft_optarg = NULL;
int ft_optind = 1;
int ft_opterr = 1;
int ft_optopt = '?';

static int parse_argument(int argc,
                          char *argv[],
                          const char *optstring,
                          const struct ft_option *longopts,
                          int *longindex);
static int
handle_long_option(int argc, char *const argv[], const struct ft_option *longopts, int *longindex);
static int handle_short_option(int argc, char *const argv[], const char *optstring);

int ft_getopt_long(int argc,
                   char *argv[],
                   const char *optstring,
                   const struct ft_option *longopts,
                   int *longindex) {
  return parse_argument(argc, argv, optstring, longopts, longindex);
}

static int parse_argument(int argc,
                          char *argv[],
                          const char *optstring,
                          const struct ft_option *longopts,
                          int *longindex) {
  if (ft_optind >= argc) {
    return -1;
  }

  char *current_arg = argv[ft_optind];

  if (current_arg[0] == '-' && current_arg[1] == '-') {
    return handle_long_option(argc, argv, longopts, longindex);
  } else if (current_arg[0] == '-' && current_arg[1] != '\0') {
    return handle_short_option(argc, argv, optstring);
  }
  char *tmp_arg = argv[ft_optind];
  for (int i = ft_optind; i < argc; i++) {
    argv[i] = argv[i + 1];
  }
  argv[argc - 1] = tmp_arg;
  return parse_argument(argc - 1, argv, optstring, longopts, longindex);
}

static int
handle_long_option(int argc, char *const argv[], const struct ft_option *longopts, int *longindex) {
  char *current_arg = argv[ft_optind] + 2;

  for (int i = 0; longopts[i].name != NULL; i++) {
    if (ft_strcmp(current_arg, longopts[i].name) == 0) {
      if (longopts[i].has_arg == ft_required_argument) {
        if (ft_optind + 1 < argc) {
          ft_optarg = argv[++ft_optind];
        } else {
          if (ft_opterr) {
            fprintf(stderr, "Option '--%s' requires an argument\n", longopts[i].name);
          }
          return '?';
        }
      } else if (longopts[i].has_arg == ft_optional_argument) {
        if (ft_optind + 1 < argc && argv[ft_optind + 1][0] != '-') {
          ft_optarg = argv[++ft_optind];
        }
      }
      ft_optind++;
      if (longindex) {
        *longindex = i;
      }
      if (longopts[i].flag) {
        *(longopts[i].flag) = longopts[i].val;
        return 0;
      }
      return longopts[i].val;
    }
  }
  if (ft_opterr) {
    fprintf(stderr, "Unknown option '--%s'\n", current_arg);
  }
  ft_optind++;
  return '?';
}

static int handle_short_option(int argc, char *const argv[], const char *optstring) {
  static int nextchar = 1;
  char *current_arg = argv[ft_optind];
  char opt = current_arg[nextchar++];
  const char *opt_decl = ft_strchr(optstring, opt);

  if (!opt_decl) {
    if (ft_opterr) {
      fprintf(stderr, "Unknown option '-%c'\n", opt);
    }
    ft_optopt = opt;
    if (!current_arg[nextchar]) {
      ft_optind++;
      nextchar = 1;
    }
    return '?';
  }

  if (*(opt_decl + 1) == ':') {
    if (current_arg[nextchar] != '\0') {
      ft_optarg = &current_arg[nextchar];
    } else if (ft_optind + 1 < argc) {
      ft_optarg = argv[++ft_optind];
    } else {
      if (ft_opterr) {
        fprintf(stderr, "Option '-%c' requires an argument\n", opt);
      }
      ft_optopt = opt;
      nextchar = 1;
      ft_optind++;
      return '?';
    }
    ft_optind++;
    nextchar = 1;
  } else {
    if (!current_arg[nextchar]) {
      ft_optind++;
      nextchar = 1;
    }
  }
  return opt;
}
