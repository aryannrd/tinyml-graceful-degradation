


    // !!! This file is generated using emlearn !!!

    #include <stdint.h>
    

static inline int32_t mytree_tree_0(const int16_t *features, int32_t features_length) {
          if (features[0] < 699) {
              return 0;
          } else {
              return 1;
          }
        }
        

int32_t mytree_predict(const int16_t *features, int32_t features_length) {

        int32_t votes[2] = {0,};
        int32_t _class = -1;

        _class = mytree_tree_0(features, features_length); votes[_class] += 1;
    
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
    

int mytree_predict_proba(const int16_t *features, int32_t features_length, float *out, int out_length) {

        int32_t _class = -1;

        for (int i=0; i<out_length; i++) {
            out[i] = 0.0f;
        }

        _class = mytree_tree_0(features, features_length); out[_class] += 1.0f;
    
        // compute mean
        for (int i=0; i<out_length; i++) {
            out[i] = out[i] / 1;
        }
        return 0;
    }
    

            int32_t
            predict_wrapper(const float *values, int length) {
                // Convert to whatever is needed for inline
                int16_t features[4];
                for (int i=0; i<length; i++) {
                    features[i] = (int16_t)values[i];
                }
                const int32_t out = mytree_predict(features, length);
                if (out < 0) {
                    return -out;
                }
                return out;
            }

            int
            predict_proba_wrapper(const float *values, int length, float *outputs, int n_outputs) {
                // Convert to whatever is needed for inline
                int16_t features[4];
                for (int i=0; i<length; i++) {
                    features[i] = (int16_t)values[i];
                }

                const int err =                     mytree_predict_proba(features, length, outputs, n_outputs);

                return err;
            }
            