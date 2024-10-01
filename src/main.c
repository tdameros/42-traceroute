#include <stdio.h>

#include "flags.h"
#include "print.h"
#include "traceroute.h"

int main(int argc, char *argv[]) {
  flags_t flags = {0};
  int8_t return_code = parse_flags(argc, argv, &flags);
  if (return_code < 0) {
    return 1;
  } else if (return_code == 0) {
    return 0;
  }

  traceroute_t traceroute = {0};
  if (init_traceroute(&traceroute, &flags) < 0) {
    return 1;
  }

  print_traceroute_start(&traceroute);
  traceroute_result_t last_result = {0};
  traceroute_result_t result;
  while (traceroute.ttl <= traceroute.max_ttl) {
    printf(" %2d  ", traceroute.ttl);
    for (uint8_t i = 0; i < traceroute.max_tries; i++) {
      result = probe_traceroute(&traceroute);
      if (result.status == TRACEROUTE_FATAL_ERROR) {
        free_traceroute(&traceroute);
        return 1;
      }
      print_traceroute_result(&result, i == 0, last_result.reply_address);
      if (result.status == TRACEROUTE_TIME_EXCEEDED) {
        last_result = result;
      }
      increment_port(&traceroute);
    }
    printf("\n");
    if (result.status == TRACEROUTE_SUCCESS) {
      break;
    }
    traceroute.ttl++;
  }
  free_traceroute(&traceroute);
  return 0;
}
