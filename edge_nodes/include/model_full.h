


    // !!! This file is generated using emlearn !!!

    #include <stdint.h>
    

static inline int32_t model_full_tree_0(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[3] < 0) {
                  if (features[2] < 1) {
                      if (features[0] < 0) {
                          return 0;
                      } else {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      return 1;
                  }
              } else {
                  if (features[2] < 1) {
                      if (features[0] < 0) {
                          return 1;
                      } else {
                          return 0;
                      }
                  } else {
                      if (features[2] < 1) {
                          return 1;
                      } else {
                          if (features[0] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  }
              }
          } else {
              if (features[0] < 0) {
                  if (features[1] < 0) {
                      return 1;
                  } else {
                      if (features[3] < 1) {
                          return 0;
                      } else {
                          return 1;
                      }
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_1(const int16_t *features, int32_t features_length) {
          if (features[2] < 1) {
              if (features[3] < 0) {
                  return 0;
              } else {
                  if (features[0] < 0) {
                      if (features[2] < 0) {
                          if (features[0] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[0] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      return 1;
                  }
              }
          } else {
              if (features[1] < 0) {
                  if (features[3] < 0) {
                      return 0;
                  } else {
                      if (features[2] < 1) {
                          return 0;
                      } else {
                          return 1;
                      }
                  }
              } else {
                  if (features[1] < 0) {
                      if (features[0] < 0) {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 1;
                          }
                      } else {
                          return 0;
                      }
                  } else {
                      return 1;
                  }
              }
          }
        }
        

static inline int32_t model_full_tree_2(const int16_t *features, int32_t features_length) {
          if (features[2] < 1) {
              if (features[3] < 0) {
                  if (features[1] < 0) {
                      return 0;
                  } else {
                      if (features[3] < 0) {
                          return 1;
                      } else {
                          if (features[0] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  }
              } else {
                  if (features[1] < 0) {
                      return 1;
                  } else {
                      if (features[0] < 0) {
                          if (features[1] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      } else {
                          return 1;
                      }
                  }
              }
          } else {
              if (features[1] < 0) {
                  if (features[2] < 1) {
                      if (features[2] < 1) {
                          return 1;
                      } else {
                          return 0;
                      }
                  } else {
                      return 1;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_3(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[0] < 0) {
                  return 0;
              } else {
                  if (features[1] < 0) {
                      if (features[3] < 0) {
                          return 0;
                      } else {
                          return 1;
                      }
                  } else {
                      if (features[0] < 0) {
                          if (features[1] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      } else {
                          return 0;
                      }
                  }
              }
          } else {
              if (features[2] < 1) {
                  if (features[2] < 1) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_4(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[1] < 0) {
                  if (features[1] < 0) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  if (features[1] < 0) {
                      if (features[0] < 0) {
                          if (features[0] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[3] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  } else {
                      if (features[2] < 1) {
                          return 0;
                      } else {
                          if (features[1] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  }
              }
          } else {
              if (features[2] < 1) {
                  if (features[2] < 1) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_5(const int16_t *features, int32_t features_length) {
          if (features[2] < 1) {
              if (features[0] < 0) {
                  if (features[0] < 0) {
                      if (features[3] < 2) {
                          return 0;
                      } else {
                          return 1;
                      }
                  } else {
                      if (features[3] < 0) {
                          return 1;
                      } else {
                          if (features[1] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      }
                  }
              } else {
                  return 1;
              }
          } else {
              if (features[1] < 0) {
                  if (features[0] < 0) {
                      return 0;
                  } else {
                      if (features[3] < 0) {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[2] < 1) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_6(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[0] < 0) {
                  if (features[3] < 2) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[2] < 0) {
                      if (features[1] < 0) {
                          return 1;
                      } else {
                          if (features[1] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      if (features[2] < 1) {
                          if (features[0] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  }
              }
          } else {
              if (features[0] < 0) {
                  if (features[0] < 0) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_7(const int16_t *features, int32_t features_length) {
          if (features[0] < 0) {
              if (features[1] < 0) {
                  if (features[1] < 0) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  if (features[1] < 0) {
                      if (features[0] < 0) {
                          return 1;
                      } else {
                          if (features[3] < 1) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      if (features[3] < 0) {
                          return 0;
                      } else {
                          if (features[2] < 1) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  }
              }
          } else {
              if (features[1] < 0) {
                  if (features[0] < 0) {
                      return 1;
                  } else {
                      if (features[1] < 0) {
                          return 1;
                      } else {
                          return 0;
                      }
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_8(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[1] < 0) {
                  if (features[3] < 2) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[1] < 0) {
                      if (features[3] < 0) {
                          return 1;
                      } else {
                          if (features[2] < 1) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  } else {
                      if (features[3] < 0) {
                          if (features[3] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[0] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  }
              }
          } else {
              if (features[1] < 0) {
                  if (features[2] < 1) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_9(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[3] < 0) {
                  if (features[2] < 1) {
                      if (features[0] < 0) {
                          return 0;
                      } else {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      return 1;
                  }
              } else {
                  if (features[1] < 0) {
                      if (features[3] < 1) {
                          return 1;
                      } else {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      if (features[3] < 1) {
                          return 0;
                      } else {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  }
              }
          } else {
              if (features[1] < 0) {
                  if (features[0] < 0) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_10(const int16_t *features, int32_t features_length) {
          if (features[0] < 0) {
              if (features[3] < 0) {
                  if (features[1] < 0) {
                      return 0;
                  } else {
                      if (features[1] < 0) {
                          if (features[2] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          return 0;
                      }
                  }
              } else {
                  if (features[0] < 0) {
                      return 0;
                  } else {
                      return 1;
                  }
              }
          } else {
              return 1;
          }
        }
        

static inline int32_t model_full_tree_11(const int16_t *features, int32_t features_length) {
          if (features[1] < 0) {
              if (features[0] < 0) {
                  if (features[3] < 2) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[0] < 0) {
                      if (features[1] < 0) {
                          return 1;
                      } else {
                          if (features[2] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  } else {
                      if (features[2] < 1) {
                          if (features[3] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[0] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  }
              }
          } else {
              return 1;
          }
        }
        

static inline int32_t model_full_tree_12(const int16_t *features, int32_t features_length) {
          if (features[0] < 0) {
              if (features[2] < 0) {
                  if (features[0] < 0) {
                      return 1;
                  } else {
                      if (features[2] < 0) {
                          return 0;
                      } else {
                          if (features[2] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  }
              } else {
                  if (features[0] < 0) {
                      return 0;
                  } else {
                      if (features[2] < 1) {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[3] < 0) {
                              return 1;
                          } else {
                              return 1;
                          }
                      }
                  }
              }
          } else {
              if (features[1] < 0) {
                  if (features[1] < 0) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t model_full_tree_13(const int16_t *features, int32_t features_length) {
          if (features[0] < 0) {
              if (features[0] < 0) {
                  if (features[1] < 0) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  if (features[0] < 0) {
                      if (features[2] < 0) {
                          if (features[0] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[3] < 1) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      if (features[2] < 1) {
                          return 0;
                      } else {
                          if (features[3] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  }
              }
          } else {
              return 1;
          }
        }
        

static inline int32_t model_full_tree_14(const int16_t *features, int32_t features_length) {
          if (features[2] < 1) {
              if (features[1] < 0) {
                  if (features[1] < 0) {
                      if (features[1] < 0) {
                          return 1;
                      } else {
                          return 0;
                      }
                  } else {
                      if (features[3] < 0) {
                          if (features[2] < 0) {
                              return 1;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[1] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  }
              } else {
                  return 1;
              }
          } else {
              if (features[1] < 0) {
                  if (features[3] < 0) {
                      if (features[1] < 0) {
                          if (features[0] < 0) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[3] < 0) {
                              return 0;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      return 1;
                  }
              } else {
                  if (features[2] < 1) {
                      if (features[1] < 0) {
                          if (features[0] < 0) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          return 1;
                      }
                  } else {
                      return 1;
                  }
              }
          }
        }
        

int32_t model_full_predict(const int16_t *features, int32_t features_length) {

        int32_t votes[2] = {0,};
        int32_t _class = -1;

        _class = model_full_tree_0(features, features_length); votes[_class] += 1;
    _class = model_full_tree_1(features, features_length); votes[_class] += 1;
    _class = model_full_tree_2(features, features_length); votes[_class] += 1;
    _class = model_full_tree_3(features, features_length); votes[_class] += 1;
    _class = model_full_tree_4(features, features_length); votes[_class] += 1;
    _class = model_full_tree_5(features, features_length); votes[_class] += 1;
    _class = model_full_tree_6(features, features_length); votes[_class] += 1;
    _class = model_full_tree_7(features, features_length); votes[_class] += 1;
    _class = model_full_tree_8(features, features_length); votes[_class] += 1;
    _class = model_full_tree_9(features, features_length); votes[_class] += 1;
    _class = model_full_tree_10(features, features_length); votes[_class] += 1;
    _class = model_full_tree_11(features, features_length); votes[_class] += 1;
    _class = model_full_tree_12(features, features_length); votes[_class] += 1;
    _class = model_full_tree_13(features, features_length); votes[_class] += 1;
    _class = model_full_tree_14(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<2; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    

int model_full_predict_proba(const int16_t *features, int32_t features_length, float *out, int out_length) {

        int32_t _class = -1;

        for (int i=0; i<out_length; i++) {
            out[i] = 0.0f;
        }

        _class = model_full_tree_0(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_1(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_2(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_3(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_4(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_5(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_6(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_7(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_8(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_9(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_10(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_11(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_12(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_13(features, features_length); out[_class] += 1.0f;
    _class = model_full_tree_14(features, features_length); out[_class] += 1.0f;
    
        // compute mean
        for (int i=0; i<out_length; i++) {
            out[i] = out[i] / 15;
        }
        return 0;
    }
    