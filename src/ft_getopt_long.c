#include <stdio.h>
#include <string.h>
#include <getopt.h>

char *optarg = NULL;
int optind = 1;
int opterr = 1;
int optopt = '?';

int parse_argument(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex);
int handle_long_option(int argc, char *const argv[], const struct option *longopts, int *longindex);
int handle_short_option(int argc, char *const argv[], const char *optstring);

int ft_getopt_long(int argc, char *const argv[], const char *optstring,
                const struct option *longopts, int *longindex) {
  return parse_argument(argc, argv, optstring, longopts, longindex);
}

int parse_argument(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex) {
  if (optind >= argc) {
    return -1;
  }

  char *current_arg = argv[optind];

  if (current_arg[0] == '-' && current_arg[1] == '-') {
    return handle_long_option(argc, argv, longopts, longindex);
  } else if (current_arg[0] == '-' && current_arg[1] != '\0') {
    return handle_short_option(argc, argv, optstring);
  }
  return -1;
}

int handle_long_option(int argc, char *const argv[], const struct option *longopts, int *longindex) {
  char *current_arg = argv[optind] + 2;

  for (int i = 0; longopts[i].name != NULL; i++) {
    if (strcmp(current_arg, longopts[i].name) == 0) {
      if (longopts[i].has_arg == required_argument) {
        if (optind + 1 < argc) {
          optarg = argv[++optind];
        } else {
          if (opterr) {
            fprintf(stderr, "Option '--%s' requires an argument\n", longopts[i].name);
          }
          return '?';
        }
      } else if (longopts[i].has_arg == optional_argument) {
        if (optind + 1 < argc && argv[optind + 1][0] != '-') {
          optarg = argv[++optind];
        }
      }
      optind++;
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
  if (opterr) {
    fprintf(stderr, "Unknown option '--%s'\n", current_arg);
  }
  optind++;
  return '?';
}

int handle_short_option(int argc, char *const argv[], const char *optstring) {
  static int nextchar = 1;
  char *current_arg = argv[optind];
  char opt = current_arg[nextchar++];
  const char *opt_decl = strchr(optstring, opt);

  if (!opt_decl) {
    if (opterr) {
      fprintf(stderr, "Unknown option '-%c'\n", opt);
    }
    optopt = opt;
    if (!current_arg[nextchar]) {
      optind++;
      nextchar = 1;
    }
    return '?';
  }

  if (*(opt_decl + 1) == ':') {
    if (current_arg[nextchar] != '\0') {
      optarg = &current_arg[nextchar];
    } else if (optind + 1 < argc) {
      optarg = argv[++optind];
    } else {
      if (opterr) {
        fprintf(stderr, "Option '-%c' requires an argument\n", opt);
      }
      optopt = opt;
      nextchar = 1;
      optind++;
      return '?';
    }
    optind++;
    nextchar = 1;
  } else {
    if (!current_arg[nextchar]) {
      optind++;
      nextchar = 1;
    }
  }
  return opt;
}
