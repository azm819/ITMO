#ifndef MLD_PROOFS_H
#define MLD_PROOFS_H

#include <string>
#include <vector>
#include "minimizator.h"

void yesA_yesB_Dis(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(A, new disjunction(A, B)));
    doc.push_back(A);
    doc.push_back(new disjunction(A, B));
} // DONE

void notA_yesB_Dis(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(B, new disjunction(A, B)));
    doc.push_back(B);
    doc.push_back(new disjunction(A, B));
} // DONE

void yesA_notB_Dis(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(A, new disjunction(A, B)));
    doc.push_back(A);
    doc.push_back(new disjunction(A, B));
} // DONE

void notA_notB_Dis(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new negation(A));
    doc.push_back(new implication(new implication(new disjunction(A, B), A),
                                  new implication(new implication(new disjunction(A, B), new negation(A)),
                                                  new negation(new disjunction(A, B)))));
    doc.push_back(new implication(new implication(A, A),
                                  new implication(new implication(B, A), new implication(new disjunction(A, B), A))));
    doc.push_back(new implication(A, new implication(A, A)));
    doc.push_back(new implication(new implication(A, new implication(A, A)),
                                  new implication(new implication(A, new implication(new implication(A, A), A)),
                                                  new implication(A, A))));
    doc.push_back(
            new implication(new implication(A, new implication(new implication(A, A), A)), new implication(A, A)));
    doc.push_back(new implication(A, new implication(new implication(A, A), A)));
    doc.push_back(new implication(A, A));
    doc.push_back(new implication(new implication(B, A), new implication(new disjunction(A, B), A)));
    doc.push_back(new implication(new implication(B, new implication(new negation(A), B)),
                                  new implication(B, new implication(B, new implication(new negation(A), B)))));
    doc.push_back(new implication(B, new implication(new negation(A), B)));
    doc.push_back(new implication(B, new implication(B, new implication(new negation(A), B))));
    doc.push_back(new implication(B, new implication(B, B)));
    doc.push_back(new implication(new implication(B, new implication(B, B)),
                                  new implication(new implication(B, new implication(new implication(B, B), B)),
                                                  new implication(B, B))));
    doc.push_back(
            new implication(new implication(B, new implication(new implication(B, B), B)), new implication(B, B)));
    doc.push_back(new implication(B, new implication(new implication(B, B), B)));
    doc.push_back(new implication(B, B));
    doc.push_back(new implication(new implication(B, B), new implication(
            new implication(B, new implication(B, new implication(new negation(A), B))),
            new implication(B, new implication(new negation(A), B)))));
    doc.push_back(new implication(new implication(B, new implication(B, new implication(new negation(A), B))),
                                  new implication(B, new implication(new negation(A), B))));
    doc.push_back(new implication(B, new implication(new negation(A), B)));
    doc.push_back(new implication(new implication(new negation(B), new implication(new negation(A), new negation(B))),
                                  new implication(B, new implication(new negation(B), new implication(new negation(A),
                                                                                                      new negation(
                                                                                                              B))))));
    doc.push_back(new implication(new negation(B), new implication(new negation(A), new negation(B))));
    doc.push_back(
            new implication(B, new implication(new negation(B), new implication(new negation(A), new negation(B)))));
    doc.push_back(new implication(new negation(B), new implication(B, new negation(B))));
    doc.push_back(new negation(B));
    doc.push_back(new implication(B, new negation(B)));
    doc.push_back(new implication(new implication(B, new negation(B)), new implication(
            new implication(B, new implication(new negation(B), new implication(new negation(A), new negation(B)))),
            new implication(B, new implication(new negation(A), new negation(B))))));
    doc.push_back(new implication(
            new implication(B, new implication(new negation(B), new implication(new negation(A), new negation(B)))),
            new implication(B, new implication(new negation(A), new negation(B)))));
    doc.push_back(new implication(B, new implication(new negation(A), new negation(B))));
    doc.push_back(new implication(new implication(new implication(new negation(A), B),
                                                  new implication(new implication(new negation(A), new negation(B)),
                                                                  new negation(new negation(A)))), new implication(B,
                                                                                                                   new implication(
                                                                                                                           new implication(
                                                                                                                                   new negation(
                                                                                                                                           A),
                                                                                                                                   B),
                                                                                                                           new implication(
                                                                                                                                   new implication(
                                                                                                                                           new negation(
                                                                                                                                                   A),
                                                                                                                                           new negation(
                                                                                                                                                   B)),
                                                                                                                                   new negation(
                                                                                                                                           new negation(
                                                                                                                                                   A)))))));
    doc.push_back(new implication(new implication(new negation(A), B),
                                  new implication(new implication(new negation(A), new negation(B)),
                                                  new negation(new negation(A)))));
    doc.push_back(new implication(B, new implication(new implication(new negation(A), B),
                                                     new implication(new implication(new negation(A), new negation(B)),
                                                                     new negation(new negation(A))))));
    doc.push_back(new implication(new implication(B, new implication(new negation(A), B)), new implication(
            new implication(B, new implication(new implication(new negation(A), B),
                                               new implication(new implication(new negation(A), new negation(B)),
                                                               new negation(new negation(A))))), new implication(B,
                                                                                                                 new implication(
                                                                                                                         new implication(
                                                                                                                                 new negation(
                                                                                                                                         A),
                                                                                                                                 new negation(
                                                                                                                                         B)),
                                                                                                                         new negation(
                                                                                                                                 new negation(
                                                                                                                                         A)))))));
    doc.push_back(new implication(new implication(B, new implication(new implication(new negation(A), B),
                                                                     new implication(new implication(new negation(A),
                                                                                                     new negation(B)),
                                                                                     new negation(new negation(A))))),
                                  new implication(B, new implication(new implication(new negation(A), new negation(B)),
                                                                     new negation(new negation(A))))));
    doc.push_back(new implication(B, new implication(new implication(new negation(A), new negation(B)),
                                                     new negation(new negation(A)))));
    doc.push_back(new implication(new implication(B, new implication(new negation(A), new negation(B))),
                                  new implication(new implication(B, new implication(
                                          new implication(new negation(A), new negation(B)),
                                          new negation(new negation(A)))),
                                                  new implication(B, new negation(new negation(A))))));
    doc.push_back(new implication(new implication(B, new implication(new implication(new negation(A), new negation(B)),
                                                                     new negation(new negation(A)))),
                                  new implication(B, new negation(new negation(A)))));
    doc.push_back(new implication(B, new negation(new negation(A))));
    doc.push_back(new implication(new implication(new negation(new negation(A)), A),
                                  new implication(B, new implication(new negation(new negation(A)), A))));
    doc.push_back(new implication(new negation(new negation(A)), A));
    doc.push_back(new implication(B, new implication(new negation(new negation(A)), A)));
    doc.push_back(new implication(new implication(B, new negation(new negation(A))),
                                  new implication(new implication(B, new implication(new negation(new negation(A)), A)),
                                                  new implication(B, A))));
    doc.push_back(new implication(new implication(B, new implication(new negation(new negation(A)), A)),
                                  new implication(B, A)));
    doc.push_back(new implication(B, A));
    doc.push_back(new implication(new disjunction(A, B), A));
    doc.push_back(new implication(new implication(new disjunction(A, B), new negation(A)),
                                  new negation(new disjunction(A, B))));
    doc.push_back(new implication(new negation(A), new implication(new disjunction(A, B), new negation(A))));
    doc.push_back(new implication(new disjunction(A, B), new negation(A)));
    doc.push_back(new negation(new disjunction(A, B)));
} // DONE

void yesA_yesB_Con(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(A, new implication(B, new conjunction(A, B))));
    doc.push_back(A);
    doc.push_back(new implication(B, new conjunction(A, B)));
    doc.push_back(B);
    doc.push_back(new conjunction(A, B));
} // DONE

void notA_yesB_Con(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(new implication(new conjunction(A, B), A),
                                  new implication(new implication(new conjunction(A, B), new negation(A)),
                                                  new negation(new conjunction(A, B)))));
    doc.push_back(new implication(new conjunction(A, B), A));
    doc.push_back(new implication(new implication(new conjunction(A, B), new negation(A)),
                                  new negation(new conjunction(A, B))));
    doc.push_back(new implication(new negation(A), new implication(new conjunction(A, B), new negation(A))));
    doc.push_back(new negation(A));
    doc.push_back(new implication(new conjunction(A, B), new negation(A)));
    doc.push_back(new negation(new conjunction(A, B)));
} // DONE

void yesA_notB_Con(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(new implication(new conjunction(A, B), B),
                                  new implication(new implication(new conjunction(A, B), new negation(B)),
                                                  new negation(new conjunction(A, B)))));
    doc.push_back(new implication(new conjunction(A, B), B));
    doc.push_back(new implication(new implication(new conjunction(A, B), new negation(B)),
                                  new negation(new conjunction(A, B))));
    doc.push_back(new implication(new negation(B), new implication(new conjunction(A, B), new negation(B))));
    doc.push_back(new negation(B));
    doc.push_back(new implication(new conjunction(A, B), new negation(B)));
    doc.push_back(new negation(new conjunction(A, B)));
} // DONE

void notA_notB_Con(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(new implication(new conjunction(A, B), A),
                                  new implication(new implication(new conjunction(A, B), new negation(A)),
                                                  new negation(new conjunction(A, B)))));
    doc.push_back(new implication(new conjunction(A, B), A));
    doc.push_back(new implication(new implication(new conjunction(A, B), new negation(A)),
                                  new negation(new conjunction(A, B))));
    doc.push_back(new implication(new negation(A), new implication(new conjunction(A, B), new negation(A))));
    doc.push_back(new negation(A));
    doc.push_back(new implication(new conjunction(A, B), new negation(A)));
    doc.push_back(new negation(new conjunction(A, B)));
} // DONE

void yesA_yesB_Imp(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(B, new implication(A, B)));
    doc.push_back(B);
    doc.push_back(new implication(A, B));
} // DONE

void notA_yesB_Imp(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(B, new implication(A, B)));
    doc.push_back(B);
    doc.push_back(new implication(A, B));
} // DONE

void yesA_notB_Imp(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(new implication(new implication(A, B), B),
                                  new implication(new implication(new implication(A, B), new negation(B)),
                                                  new negation(new implication(A, B)))));
    doc.push_back(new implication(new implication(new implication(A, B), A),
                                  new implication(new implication(new implication(A, B), new implication(A, B)),
                                                  new implication(new implication(A, B), B))));
    doc.push_back(A);
    doc.push_back(new implication(A, new implication(new implication(A, B), A)));
    doc.push_back(new implication(new implication(A, B), A));
    doc.push_back(new implication(new implication(new implication(A, B), new implication(A, B)),
                                  new implication(new implication(A, B), B)));
    doc.push_back(
            new implication(new implication(A, B), new implication(new implication(A, B), new implication(A, B))));
    doc.push_back(new implication(
            new implication(new implication(A, B), new implication(new implication(A, B), new implication(A, B))),
            new implication(new implication(new implication(A, B), new implication(
                    new implication(new implication(A, B), new implication(A, B)), new implication(A, B))),
                            new implication(new implication(A, B), new implication(A, B)))));
    doc.push_back(new implication(new implication(new implication(A, B), new implication(
            new implication(new implication(A, B), new implication(A, B)), new implication(A, B))),
                                  new implication(new implication(A, B), new implication(A, B))));
    doc.push_back(new implication(new implication(A, B),
                                  new implication(new implication(new implication(A, B), new implication(A, B)),
                                                  new implication(A, B))));
    doc.push_back(new implication(new implication(A, B), new implication(A, B)));
    doc.push_back(new implication(new implication(A, B), B));
    doc.push_back(new implication(new negation(B), new implication(new implication(A, B), new negation(B))));
    doc.push_back(new implication(new negation(B), new implication(new implication(A, B), new negation(B))));
    doc.push_back(new negation(B));
    doc.push_back(new implication(new implication(A, B), new negation(B)));
    doc.push_back(new implication(new implication(new implication(A, B), new negation(B)),
                                  new negation(new implication(A, B))));
    doc.push_back(new negation(new implication(A, B)));
} // DONE

void notA_notB_Imp(expression *A, expression *B, std::vector<expression *> &doc) {
    doc.push_back(new implication(new implication(A, new implication(new negation(B), A)),
                                  new implication(A, new implication(A, new implication(new negation(B), A)))));
    doc.push_back(new implication(A, new implication(new negation(B), A)));
    doc.push_back(new implication(A, new implication(A, new implication(new negation(B), A))));
    doc.push_back(new implication(A, new implication(A, A)));
    doc.push_back(new implication(new implication(A, new implication(A, A)),
                                  new implication(new implication(A, new implication(new implication(A, A), A)),
                                                  new implication(A, A))));
    doc.push_back(
            new implication(new implication(A, new implication(new implication(A, A), A)), new implication(A, A)));
    doc.push_back(new implication(A, new implication(new implication(A, A), A)));
    doc.push_back(new implication(A, A));
    doc.push_back(new implication(new implication(A, A), new implication(
            new implication(A, new implication(A, new implication(new negation(B), A))),
            new implication(A, new implication(new negation(B), A)))));
    doc.push_back(new implication(new implication(A, new implication(A, new implication(new negation(B), A))),
                                  new implication(A, new implication(new negation(B), A))));
    doc.push_back(new implication(A, new implication(new negation(B), A)));
    doc.push_back(new implication(new implication(new negation(A), new implication(new negation(B), new negation(A))),
                                  new implication(A, new implication(new negation(A), new implication(new negation(B),
                                                                                                      new negation(
                                                                                                              A))))));
    doc.push_back(new implication(new negation(A), new implication(new negation(B), new negation(A))));
    doc.push_back(
            new implication(A, new implication(new negation(A), new implication(new negation(B), new negation(A)))));
    doc.push_back(new implication(new negation(A), new implication(A, new negation(A))));
    doc.push_back(new negation(A));
    doc.push_back(new implication(A, new negation(A)));
    doc.push_back(new implication(new implication(A, new negation(A)), new implication(
            new implication(A, new implication(new negation(A), new implication(new negation(B), new negation(A)))),
            new implication(A, new implication(new negation(B), new negation(A))))));
    doc.push_back(new implication(
            new implication(A, new implication(new negation(A), new implication(new negation(B), new negation(A)))),
            new implication(A, new implication(new negation(B), new negation(A)))));
    doc.push_back(new implication(A, new implication(new negation(B), new negation(A))));
    doc.push_back(new implication(new implication(new implication(new negation(B), A),
                                                  new implication(new implication(new negation(B), new negation(A)),
                                                                  new negation(new negation(B)))), new implication(A,
                                                                                                                   new implication(
                                                                                                                           new implication(
                                                                                                                                   new negation(
                                                                                                                                           B),
                                                                                                                                   A),
                                                                                                                           new implication(
                                                                                                                                   new implication(
                                                                                                                                           new negation(
                                                                                                                                                   B),
                                                                                                                                           new negation(
                                                                                                                                                   A)),
                                                                                                                                   new negation(
                                                                                                                                           new negation(
                                                                                                                                                   B)))))));
    doc.push_back(new implication(new implication(new negation(B), A),
                                  new implication(new implication(new negation(B), new negation(A)),
                                                  new negation(new negation(B)))));
    doc.push_back(new implication(A, new implication(new implication(new negation(B), A),
                                                     new implication(new implication(new negation(B), new negation(A)),
                                                                     new negation(new negation(B))))));
    doc.push_back(new implication(new implication(A, new implication(new negation(B), A)), new implication(
            new implication(A, new implication(new implication(new negation(B), A),
                                               new implication(new implication(new negation(B), new negation(A)),
                                                               new negation(new negation(B))))), new implication(A,
                                                                                                                 new implication(
                                                                                                                         new implication(
                                                                                                                                 new negation(
                                                                                                                                         B),
                                                                                                                                 new negation(
                                                                                                                                         A)),
                                                                                                                         new negation(
                                                                                                                                 new negation(
                                                                                                                                         B)))))));
    doc.push_back(new implication(new implication(A, new implication(new implication(new negation(B), A),
                                                                     new implication(new implication(new negation(B),
                                                                                                     new negation(A)),
                                                                                     new negation(new negation(B))))),
                                  new implication(A, new implication(new implication(new negation(B), new negation(A)),
                                                                     new negation(new negation(B))))));
    doc.push_back(new implication(A, new implication(new implication(new negation(B), new negation(A)),
                                                     new negation(new negation(B)))));
    doc.push_back(new implication(new implication(A, new implication(new negation(B), new negation(A))),
                                  new implication(new implication(A, new implication(
                                          new implication(new negation(B), new negation(A)),
                                          new negation(new negation(B)))),
                                                  new implication(A, new negation(new negation(B))))));
    doc.push_back(new implication(new implication(A, new implication(new implication(new negation(B), new negation(A)),
                                                                     new negation(new negation(B)))),
                                  new implication(A, new negation(new negation(B)))));
    doc.push_back(new implication(A, new negation(new negation(B))));
    doc.push_back(new implication(new implication(new negation(new negation(B)), B),
                                  new implication(A, new implication(new negation(new negation(B)), B))));
    doc.push_back(new implication(new negation(new negation(B)), B));
    doc.push_back(new implication(A, new implication(new negation(new negation(B)), B)));
    doc.push_back(new implication(new implication(A, new negation(new negation(B))),
                                  new implication(new implication(A, new implication(new negation(new negation(B)), B)),
                                                  new implication(A, B))));
    doc.push_back(new implication(new implication(A, new implication(new negation(new negation(B)), B)),
                                  new implication(A, B)));
    doc.push_back(new implication(A, B));

} // DONE

void yesA_Neg(expression *A, std::vector<expression *> &doc) {
    doc.push_back(new implication(A, new implication(new negation(A), A)));
    doc.push_back(A);
    doc.push_back(new implication(new negation(A), A));
    doc.push_back(new implication(new negation(A),
                                  new implication(new implication(new negation(A), new negation(A)), new negation(A))));
    doc.push_back(new implication(new negation(A), new implication(new negation(A), new negation(A))));
    doc.push_back(new implication(new implication(new negation(A), new implication(new negation(A), new negation(A))),
                                  new implication(new implication(new negation(A), new implication(
                                          new implication(new negation(A), new negation(A)), new negation(A))),
                                                  new implication(new negation(A), new negation(A)))));
    doc.push_back(new implication(new implication(new negation(A),
                                                  new implication(new implication(new negation(A), new negation(A)),
                                                                  new negation(A))),
                                  new implication(new negation(A), new negation(A))));
    doc.push_back(new implication(new negation(A), new negation(A)));
    doc.push_back(new implication(new implication(new negation(A), A),
                                  new implication(new implication(new negation(A), new negation(A)),
                                                  new negation(new negation(A)))));
    doc.push_back(new implication(new implication(new negation(A), new negation(A)), new negation(new negation(A))));
    doc.push_back(new negation(new negation(A)));

} // DONE

void notA_Neg(expression *A, std::vector<expression *> &doc) {
    doc.push_back(new negation(A));
} // DONE

void B_or_not_B(expression *A, std::vector<expression *> &doc) {
    doc.push_back(new implication(A, new disjunction(A, new negation(A))));
    doc.push_back(new implication(new negation(A), new disjunction(A, new negation(A))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(A, new disjunction(A, new negation(A))))));
    doc.push_back(new implication(new implication(
            new implication(new implication(A, new disjunction(A, new negation(A))),
                            new implication(new implication(A, new negation(new disjunction(A, new negation(A)))),
                                            new negation(A))),
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                                    new implication(A, new negation(new disjunction(A, new negation(A)))),
                                    new negation(A))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A))), new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new disjunction(A,
                                                                                                             new negation(
                                                                                                                     A))),
                                                                          new implication(new implication(A,
                                                                                                          new negation(
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A)))),
                                                                                          new negation(A))))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(A, new negation(
                                                          new disjunction(A, new negation(A)))), new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                          new implication(A, new disjunction(A, new negation(A))), new implication(
                                                  new implication(A, new negation(new disjunction(A, new negation(A)))),
                                                  new negation(A))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
            new implication(new implication(A, new disjunction(A, new negation(A))),
                            new implication(new implication(A, new negation(new disjunction(A, new negation(A)))),
                                            new negation(A))),
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                                    new implication(A, new negation(new disjunction(A, new negation(A)))),
                                    new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(A, new negation(
                                                          new disjunction(A, new negation(A)))), new negation(A))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(
                                                          new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new implication(A, new negation(new disjunction(A, new negation(A)))),
                                                  new negation(A))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(A, new negation(
                                                          new disjunction(A, new negation(A)))), new negation(A)))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(
                                                          new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A)))), new implication(
            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                    new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                            new implication(A, new negation(new disjunction(A, new negation(A)))), new negation(A))),
                    new implication(new negation(new disjunction(A, new negation(A))),
                                    new implication(new implication(A, new disjunction(A, new negation(A))),
                                                    new implication(new implication(A, new negation(
                                                            new disjunction(A, new negation(A)))), new negation(A)))))),
            new implication(new implication(A, new disjunction(A, new negation(A))),
                            new implication(new negation(new disjunction(A, new negation(A))),
                                            new implication(new implication(A, new disjunction(A, new negation(A))),
                                                            new implication(new implication(A, new negation(
                                                                    new disjunction(A, new negation(A)))),
                                                                            new negation(A))))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A))), new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new disjunction(A,
                                                                                                             new negation(
                                                                                                                     A))),
                                                                          new implication(new implication(A,
                                                                                                          new negation(
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A)))),
                                                                                          new negation(A)))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new disjunction(A,
                                                                                                                     new negation(
                                                                                                                             A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A)))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                          new implication(A, new disjunction(A, new negation(A))), new implication(
                                                  new implication(A, new negation(new disjunction(A, new negation(A)))),
                                                  new negation(A))))));
    doc.push_back(new implication(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(A,
                                                                                  new disjunction(A, new negation(A)))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new disjunction(A,
                                                                                                             new negation(
                                                                                                                     A))),
                                                                          new implication(new implication(A,
                                                                                                          new negation(
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A)))),
                                                                                          new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(A, new disjunction(A, new negation(A)))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  A,
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A))),
                                                                                                          new implication(
                                                                                                                  new implication(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  new disjunction(
                                                                                                                                          A,
                                                                                                                                          new negation(
                                                                                                                                                  A)))),
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(A, new disjunction(A, new negation(A)))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new disjunction(A,
                                                                                                                     new negation(
                                                                                                                             A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A)))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))),
                                                                                  new negation(A))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(A, new disjunction(A, new negation(A)))), new implication(
                    new implication(new negation(new disjunction(A, new negation(A))),
                                    new implication(new implication(A, new disjunction(A, new negation(A))),
                                                    new implication(new implication(A, new negation(
                                                            new disjunction(A, new negation(A)))), new negation(A)))),
                    new implication(new negation(new disjunction(A, new negation(A))), new implication(
                            new implication(A, new negation(new disjunction(A, new negation(A)))),
                            new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(A, new disjunction(A, new negation(
                                                                          A))))), new implication(
            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                    new implication(new negation(new disjunction(A, new negation(A))),
                                    new implication(A, new disjunction(A, new negation(A)))), new implication(
                            new implication(new negation(new disjunction(A, new negation(A))),
                                            new implication(new implication(A, new disjunction(A, new negation(A))),
                                                            new implication(new implication(A, new negation(
                                                                    new disjunction(A, new negation(A)))),
                                                                            new negation(A)))),
                            new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                    new implication(A, new negation(new disjunction(A, new negation(A)))),
                                    new negation(A)))))),
            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                    new implication(new negation(new disjunction(A, new negation(A))),
                                    new implication(new implication(A, new disjunction(A, new negation(A))),
                                                    new implication(new implication(A, new negation(
                                                            new disjunction(A, new negation(A)))), new negation(A)))),
                    new implication(new negation(new disjunction(A, new negation(A))), new implication(
                            new implication(A, new negation(new disjunction(A, new negation(A)))),
                            new negation(A))))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(A, new disjunction(A, new negation(A)))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  A,
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A))),
                                                                                                          new implication(
                                                                                                                  new implication(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  new disjunction(
                                                                                                                                          A,
                                                                                                                                          new negation(
                                                                                                                                                  A)))),
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  A)))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new disjunction(A,
                                                                                                             new negation(
                                                                                                                     A))),
                                                                          new implication(new implication(A,
                                                                                                          new negation(
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A)))),
                                                                                          new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A)))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                                    new implication(A, new negation(new disjunction(A, new negation(A)))),
                                    new negation(A)))),
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(new implication(A, new negation(new disjunction(A, new negation(A)))),
                                            new negation(A))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new disjunction(A,
                                                                                                                     new negation(
                                                                                                                             A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A))))),
                                  new implication(
                                          new implication(new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(
                                                                  new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new disjunction(A,
                                                                                                                     new negation(
                                                                                                                             A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A)))),
                                                                          new implication(new negation(
                                                                                  new disjunction(A, new negation(A))),
                                                                                          new implication(
                                                                                                  new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A))))),
                                          new implication(new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(
                                                                  new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))),
                                                                                  new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new disjunction(A,
                                                                                                             new negation(
                                                                                                                     A))),
                                                                          new implication(new implication(A,
                                                                                                          new negation(
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A)))),
                                                                                          new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                  new negation(A))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))),
                                                                                  new negation(A))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                          new implication(A, new negation(new disjunction(A, new negation(A)))),
                                          new negation(A)))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))), new implication(A,
                                                                                                                     new negation(
                                                                                                                             new disjunction(
                                                                                                                                     A,
                                                                                                                                     new negation(
                                                                                                                                             A))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(A, new negation(
                                                                          new disjunction(A, new negation(A))))))));
    doc.push_back(new implication(new negation(new disjunction(A, new negation(A))),
                                  new implication(A, new negation(new disjunction(A, new negation(A))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(A,
                                                                                                                     new negation(
                                                                                                                             new disjunction(
                                                                                                                                     A,
                                                                                                                                     new negation(
                                                                                                                                             A)))))));
    doc.push_back(new implication(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(A, new negation(
                                                                          new disjunction(A, new negation(A))))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A))), new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new negation(A)))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(A, new negation(
                                                                  new disjunction(A, new negation(A))))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new negation(A)))))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))), new implication(A,
                                                                                                                     new negation(
                                                                                                                             new disjunction(
                                                                                                                                     A,
                                                                                                                                     new negation(
                                                                                                                                             A))))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))),
                                                                                  new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(A)))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(A, new negation(new disjunction(A, new negation(A))))), new implication(
                    new implication(new negation(new disjunction(A, new negation(A))), new implication(
                            new implication(A, new negation(new disjunction(A, new negation(A)))), new negation(A))),
                    new implication(new negation(new disjunction(A, new negation(A))), new negation(A))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))))),
                                  new implication(
                                          new implication(new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(
                                                                  new negation(new disjunction(A, new negation(A))),
                                                                  new implication(A, new negation(
                                                                          new disjunction(A, new negation(A))))),
                                                                          new implication(new implication(new negation(
                                                                                  new disjunction(A, new negation(A))),
                                                                                                          new implication(
                                                                                                                  new implication(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  new disjunction(
                                                                                                                                          A,
                                                                                                                                          new negation(
                                                                                                                                                  A)))),
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                          new implication(new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                                          new negation(
                                                                                                                  A))))),
                                          new implication(new implication(A, new disjunction(A, new negation(A))),
                                                          new implication(new implication(
                                                                  new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))),
                                                                                  new negation(A))), new implication(
                                                                  new negation(new disjunction(A, new negation(A))),
                                                                  new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(A, new negation(
                                                                  new disjunction(A, new negation(A))))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new negation(A))))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A))), new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new negation(A))))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
            new implication(new negation(new disjunction(A, new negation(A))),
                            new implication(new implication(A, new negation(new disjunction(A, new negation(A)))),
                                            new negation(A))),
            new implication(new negation(new disjunction(A, new negation(A))), new negation(A)))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(A, new negation(
                                                                          new disjunction(A, new negation(A)))),
                                                                                  new negation(A)))), new implication(
            new implication(new implication(A, new disjunction(A, new negation(A))), new implication(
                    new implication(new negation(new disjunction(A, new negation(A))), new implication(
                            new implication(A, new negation(new disjunction(A, new negation(A)))), new negation(A))),
                    new implication(new negation(new disjunction(A, new negation(A))), new negation(A)))),
            new implication(new implication(A, new disjunction(A, new negation(A))),
                            new implication(new negation(new disjunction(A, new negation(A))), new negation(A))))));
    doc.push_back(new implication(new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(A, new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(A))), new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new negation(A)))),
                                  new implication(new implication(A, new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(A)))));
    doc.push_back(new implication(new implication(A, new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new negation(A))));
    doc.push_back(new implication(new negation(new disjunction(A, new negation(A))), new negation(A)));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(new negation(A),
                                                                  new disjunction(A, new negation(A))))));
    doc.push_back(new implication(new implication(
            new implication(new implication(new negation(A), new disjunction(A, new negation(A))), new implication(
                    new implication(new negation(A), new negation(new disjunction(A, new negation(A)))),
                    new negation(new negation(A)))), new implication(new negation(new disjunction(A, new negation(A))),
                                                                     new implication(new implication(new negation(A),
                                                                                                     new disjunction(A,
                                                                                                                     new negation(
                                                                                                                             A))),
                                                                                     new implication(new implication(
                                                                                             new negation(A),
                                                                                             new negation(
                                                                                                     new disjunction(A,
                                                                                                                     new negation(
                                                                                                                             A)))),
                                                                                                     new negation(
                                                                                                             new negation(
                                                                                                                     A)))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new negation(A), new negation(
                                                          new disjunction(A, new negation(A)))),
                                                                  new negation(new negation(A)))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(new implication(new negation(A), new negation(
                                                  new disjunction(A, new negation(A)))),
                                                          new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(new implication(new negation(A), new negation(
                                                  new disjunction(A, new negation(A)))),
                                                          new negation(new negation(A)))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new negation(A), new negation(
                                                          new disjunction(A, new negation(A)))),
                                                                  new negation(new negation(A)))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(new negation(A),
                                                                  new negation(new disjunction(A, new negation(A)))),
                                                  new negation(new negation(A)))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new negation(A), new negation(
                                                          new disjunction(A, new negation(A)))),
                                                                  new negation(new negation(A))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                  new implication(new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(new implication(
                                                  new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new negation(A), new negation(
                                                          new disjunction(A, new negation(A)))),
                                                                  new negation(new negation(A)))), new implication(
                                                  new negation(new disjunction(A, new negation(A))), new implication(
                                                          new implication(new negation(A),
                                                                          new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(new negation(A))))))),
                                                  new implication(new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A))))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(new implication(new negation(A), new negation(
                                                  new disjunction(A, new negation(A)))),
                                                          new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A)))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                          new implication(
                                                                                  new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A)))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new negation(A),
                                                                          new disjunction(A, new negation(A)))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A))),
                                                                                                          new implication(
                                                                                                                  new implication(
                                                                                                                          new negation(
                                                                                                                                  A),
                                                                                                                          new negation(
                                                                                                                                  new disjunction(
                                                                                                                                          A,
                                                                                                                                          new negation(
                                                                                                                                                  A)))),
                                                                                                                  new negation(
                                                                                                                          new negation(
                                                                                                                                  A))))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))))))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(new negation(A),
                                                                  new disjunction(A, new negation(A)))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A)))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                          new implication(
                                                                                  new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A), new disjunction(A,
                                                                                                                   new negation(
                                                                                                                           A))))),
                                  new implication(new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A)))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                          new implication(
                                                                                  new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))),
                                                  new implication(new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A))),
                                                                                                          new implication(
                                                                                                                  new implication(
                                                                                                                          new negation(
                                                                                                                                  A),
                                                                                                                          new negation(
                                                                                                                                  new disjunction(
                                                                                                                                          A,
                                                                                                                                          new negation(
                                                                                                                                                  A)))),
                                                                                                                  new negation(
                                                                                                                          new negation(
                                                                                                                                  A))))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new negation(A),
                                                                          new disjunction(A, new negation(A)))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new disjunction(
                                                                                                                          A,
                                                                                                                          new negation(
                                                                                                                                  A))),
                                                                                                          new implication(
                                                                                                                  new implication(
                                                                                                                          new negation(
                                                                                                                                  A),
                                                                                                                          new negation(
                                                                                                                                  new disjunction(
                                                                                                                                          A,
                                                                                                                                          new negation(
                                                                                                                                                  A)))),
                                                                                                                  new negation(
                                                                                                                          new negation(
                                                                                                                                  A))))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A))))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                          new implication(
                                                                                  new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A)))))),
                                  new implication(new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))))),
                                                  new implication(new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A),
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                          new implication(
                                                                                  new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new implication(new implication(
                                                                                          new negation(A), new negation(
                                                                                                  new disjunction(A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A)))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))), new implication(
                                          new implication(new negation(A),
                                                          new negation(new disjunction(A, new negation(A)))),
                                          new negation(new negation(A))))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(new negation(A),
                                                                  new negation(new disjunction(A, new negation(A))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A), new negation(
                                                                          new disjunction(A, new negation(A))))))));
    doc.push_back(new implication(new negation(new disjunction(A, new negation(A))),
                                  new implication(new negation(A), new negation(new disjunction(A, new negation(A))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(new negation(A),
                                                                  new negation(new disjunction(A, new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A), new negation(
                                                                          new disjunction(A, new negation(A))))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new negation(new negation(A))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A))))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                  new implication(new negation(A),
                                                                  new negation(new disjunction(A, new negation(A))))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(new negation(A))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A), new negation(
                                                                          new disjunction(A, new negation(A))))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A), new negation(
                                                                          new disjunction(A, new negation(A)))))),
                                  new implication(new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new negation(A), new negation(
                                                                          new disjunction(A, new negation(A))))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new negation(new negation(A)))))),
                                                  new implication(new implication(new negation(A),
                                                                                  new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A))))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A))))),
                                                                  new implication(new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                                  new implication(
                                                                                                          new implication(
                                                                                                                  new negation(
                                                                                                                          A),
                                                                                                                  new negation(
                                                                                                                          new disjunction(
                                                                                                                                  A,
                                                                                                                                  new negation(
                                                                                                                                          A)))),
                                                                                                          new negation(
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new implication(new negation(
                                                                                          new disjunction(A,
                                                                                                          new negation(
                                                                                                                  A))),
                                                                                                  new negation(
                                                                                                          new negation(
                                                                                                                  A)))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(new negation(A))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A))))),
                                  new implication(new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new implication(new implication(new negation(A),
                                                                                                  new negation(
                                                                                                          new disjunction(
                                                                                                                  A,
                                                                                                                  new negation(
                                                                                                                          A)))),
                                                                                  new negation(new negation(A)))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(new negation(A))))), new implication(
                                          new implication(new negation(A), new disjunction(A, new negation(A))),
                                          new implication(new negation(new disjunction(A, new negation(A))),
                                                          new negation(new negation(A)))))));
    doc.push_back(new implication(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new implication(
                                                          new negation(new disjunction(A, new negation(A))),
                                                          new implication(new implication(new negation(A), new negation(
                                                                  new disjunction(A, new negation(A)))),
                                                                          new negation(new negation(A)))),
                                                                  new implication(new negation(
                                                                          new disjunction(A, new negation(A))),
                                                                                  new negation(new negation(A))))),
                                  new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(new negation(A))))));
    doc.push_back(new implication(new implication(new negation(A), new disjunction(A, new negation(A))),
                                  new implication(new negation(new disjunction(A, new negation(A))),
                                                  new negation(new negation(A)))));
    doc.push_back(new implication(new negation(new disjunction(A, new negation(A))), new negation(new negation(A))));
    doc.push_back(new implication(new implication(new negation(new disjunction(A, new negation(A))), new negation(A)),
                                  new implication(new implication(new negation(new disjunction(A, new negation(A))),
                                                                  new negation(new negation(A))),
                                                  new negation(new negation(new disjunction(A, new negation(A)))))));
    doc.push_back(new implication(
            new implication(new negation(new disjunction(A, new negation(A))), new negation(new negation(A))),
            new negation(new negation(new disjunction(A, new negation(A))))));
    doc.push_back(new negation(new negation(new disjunction(A, new negation(A)))));
    doc.push_back(new implication(new negation(new negation(new disjunction(A, new negation(A)))),
                                  new disjunction(A, new negation(A))));
    doc.push_back(new disjunction(A, new negation(A)));
} // DONE

void
deduct(std::string A, std::vector<expression *> &yesA, std::vector<expression *> &notA, std::vector<expression *> &doc,
       std::vector<expression *> hypothesis) {
    auto AA = new variable(A);
    auto tmp = yesA.back();
    std::vector<expression *> docoz;
    std::vector<std::pair<int, int>> axioms;
    hypothesis.push_back(AA);
    minimize(yesA, hypothesis, docoz, axioms);
    for (int i: Answer) {
        switch (axioms[i].first) {
            case -1: {
                doc.push_back(docoz[i]);
                doc.push_back(new implication(docoz[i], new implication(AA, docoz[i])));
                break;
            }
            case -2: {
                if (equal(docoz[i], AA)) {
                    doc.push_back(new implication(AA, new implication(AA, AA)));
                    doc.push_back(new implication(new implication(AA, new implication(AA, AA)), new implication(
                            new implication(AA, new implication(new implication(AA, AA), AA)),
                            new implication(AA, AA))));
                    doc.push_back(new implication(new implication(AA, new implication(new implication(AA, AA), AA)),
                                                  new implication(AA, AA)));
                    doc.push_back(new implication(AA, new implication(new implication(AA, AA), AA)));
                    doc.push_back(new implication(AA, AA));
                } else {
                    doc.push_back(docoz[i]);
                    doc.push_back(new implication(docoz[i], new implication(AA, docoz[i])));
                }
                break;
            }
            default: {
                auto I = docoz[axioms[i].first]->getRight();
                auto J = docoz[axioms[i].first]->getLeft();
                doc.push_back(new implication(new implication(AA, J),
                                              new implication(new implication(AA, new implication(J, I)),
                                                              new implication(AA, I))));
                doc.push_back(new implication(new implication(AA, new implication(J, I)), new implication(AA, I)));
                break;
            }
        }
        doc.push_back(new implication(AA, docoz[i]));
    }

    hypothesis.pop_back();
    auto AB = new negation(AA);
    hypothesis.push_back(AB);
    docoz.clear(); // TODO
    axioms.clear();

    minimize(notA, hypothesis, docoz, axioms);
    for (int i: Answer) {
        switch (axioms[i].first) {
            case -1: {
                doc.push_back(docoz[i]);
                doc.push_back(new implication(docoz[i], new implication(AB, docoz[i])));
                break;
            }
            case -2: {
                if (equal(docoz[i], AB)) {
                    doc.push_back(new implication(AB, new implication(AB, AB)));
                    doc.push_back(new implication(new implication(AB, new implication(AB, AB)), new implication(
                            new implication(AB, new implication(new implication(AB, AB), AB)),
                            new implication(AB, AB))));
                    doc.push_back(new implication(new implication(AB, new implication(new implication(AB, AB), AB)),
                                                  new implication(AB, AB)));
                    doc.push_back(new implication(AB, new implication(new implication(AB, AB), AB)));
                    doc.push_back(new implication(AB, AB));
                } else {
                    doc.push_back(docoz[i]);
                    doc.push_back(new implication(docoz[i], new implication(AB, docoz[i])));
                }
                break;
            }
            default: {
                auto I = docoz[axioms[i].first]->getRight();
                auto J = docoz[axioms[i].first]->getLeft();
                doc.push_back(new implication(new implication(AB, J),
                                              new implication(new implication(AB, new implication(J, I)),
                                                              new implication(AB, I))));
                doc.push_back(new implication(new implication(AB, new implication(J, I)), new implication(AB, I)));
                break;
            }
        }
        doc.push_back(new implication(AB, docoz[i]));
    }

    doc.push_back(new implication(new implication(AA, tmp), new implication(new implication(AB, tmp),
                                                                            new implication(new disjunction(AA, AB),
                                                                                            (tmp)))));
    doc.push_back(new implication(new implication(AB, tmp), new implication(new disjunction(AA, AB), tmp)));
    doc.push_back(new implication(new disjunction(AA, AB), tmp));
    B_or_not_B(AA, doc);
    doc.push_back(tmp);
}

#endif //MLD_PROOFS_H
