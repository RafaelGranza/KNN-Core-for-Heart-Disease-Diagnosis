#include "src/knn_core.h"
#include "src/knn_core.cpp"
#include "src/entity.h"

int main(int argc, char const *argv[])
{
    knn_core knn;
    double buf_d;
    char buf_c;
    for (int k = 1; k < 250; ++k)
    {
        FILE* file = fopen("src/heart.csv","r");
        char header[512];
        entity ent;
        fscanf(file, "%s", header);
        int true_pos_1 = 0;
        int true_neg_1 = 0;
        int false_pos_1 = 0;
        int false_neg_1 = 0;
        int true_pos_2 = 0;
        int true_neg_2 = 0;
        int false_pos_2 = 0;
        int false_neg_2 = 0;
        while (fscanf(file, "%lf%c", &buf_d, &buf_c) == 2)
        {
            ent.values.push_back(buf_d);    
            if (buf_c != ',')
            {
                ent.positive = buf_d;
                if (ent.positive == knn.classify_1(ent, k))
                {
                    if (ent.positive) ++true_pos_1;
                    else ++true_neg_1;
                }
                else
                {
                    if (ent.positive) ++false_neg_1;
                    else ++false_pos_1;
                }
                
                if (ent.positive == knn.classify_2(ent, k))
                {
                    if (ent.positive) ++true_pos_2;
                    else ++true_neg_2;
                }
                else
                {
                    if (ent.positive) ++false_neg_2;
                    else ++false_pos_2;
                }
                ent = entity();
            }
        }
        double acur_1 = (true_neg_1+true_pos_1)/40.0;
        double prec_1 = (true_pos_1)/(true_pos_1+0.0+false_pos_1);
        double reca_1 = (true_pos_1)/(true_pos_1+0.0+false_neg_1);
        double f1_s_1 = (2*prec_1*reca_1)/(prec_1 + reca_1);
        double acur_2 = (true_neg_2+true_pos_2)/40.0;
        double prec_2 = (true_pos_2)/(true_pos_2+0.0+false_pos_2);
        double reca_2 = (true_pos_2)/(true_pos_2+0.0+false_neg_2);
        double f1_s_2 = (2*prec_2*reca_2)/(prec_2 + reca_2);
        printf("%lf ",  acur_1);
        printf("%lf ",  prec_1);
        printf("%lf ",  reca_1);
        printf("%lf ",  f1_s_1);
        printf("%lf ",  acur_2);
        printf("%lf ",  prec_2);
        printf("%lf ",  reca_2);
        printf("%lf\n", f1_s_2);
        fflush(stdout);
        free(file);
        if(k == 248) exit(0);
    }
     return 0;
}
