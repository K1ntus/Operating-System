/* putstring.c
 *	Simple program to test whether the PutString Syscall works. 
 *  The user do not have anything to do, except analysis the output. 
 *  
 *	It is sending multiple String, testing the following:
 *      \* \0
 *      \* String without an \0 at the end
 *      \* \n\0
 *      \* String with some \n in it
 *      \* Some basics Strings
 *      \* Very large string (4990+) characters
 * 
 */
#include "syscall.h"

int main() {  

    PutString("Chaine Vide:\n> \0");
    PutString("\0");

    PutString("Chaine sans caractère \\0 ni \\n:\n> \0");
    PutString("Bonjour");
    PutString("\n\0");


    PutString("Chaine1.\nChaine 2. Il ne devrait rien y avoir derrière:\n\0 Si ce message est affiché, alors c'est un FAILURE \n\0");


    PutString("Chaine1.\n\0");
    PutString("Voici la seconde chaine.\n\0");
    PutString("Finalement, nous devons tester cet appel systeme avec une chaine de caracteres conséquentes.\n \t * La voici.\n\0");

    PutString("Chaine Depassant la taille du buffer:\n> \0");
    
    //PutString("sand appreciate portion disappoint state letter regret accumulation premium patent club endure trust convention crevice equinox uncle reptile motorcycle duck soul inappropriate combination paint influence nationalism laboratory discourage abuse convulsion office cap cell phone feedback wear riot jockey route define miracle veil revoke lifestyle dividend mark variety thought marble dose treat push rocket exempt aviation ride activity prosecute exit promote reconcile insurance beam spine element ankle spin remain persist listen clean drown exception viable rehabilitation coincidence psychology exercise spite prisoner breeze observation charm package dry flourish slide correspondence freedom grass watch thread manual medium Mars restaurant step contribution genetic say fan bare message concept variation gradient document fur sex class architecture remember graze keep witness implicit native hallway coffee relaxation irony breathe courtship digress achieve precedent want expertise short circuit frank opposite explain vat pottery singer tile cemetery rabbit magnetic predict radiation ceremony absorption mail carrier commerce sustain volunteer handy outlook repeat oppose fail village constitution consideration carrot book transform countryside chew rock splurge complete wire passion confrontation sock cage thirsty jail chain introduction insist stay cheap black criticism comedy quantity patient deter level neighbour reception home frown cute slip AIDS executive communist premature folklore crystal minor technique grant relax advice hell personal interference enter woman crude liberty sunrise assault calorie character crop soup stab nose torch neck bear displace extent arrogant extraterrestrial call liver thinker breakfast neglect bottom mine act monster cotton morale reluctance myth copy move source sow constellation victory embarrassment mist earwax scan branch extension solid write bring day solve vegetable lead debate determine information sniff edge opera rest recommendation ferry boy ask anger bite acquaintance distortion goalkeeper instal sick new waiter steel garage thigh chief thaw left try fool incongruous medicine salt stereotype error ash inside mind responsible confront proud apology vegetarian relative record swear conservation vessel sea producer truth long ton bend protection quarrel matter wife dip salmon glove precede dance horse cafe count brave lover spill style analysis subject expression sheet overwhelm abstract cupboard effect ally final comfortable referral concede quit proclaim eaux intensify tense conspiracy arise install contraction result pedestrian kick sport tempt software ear secretary announcement mouth scramble amputate parameter grave coach withdraw minimum machinery standard provide sell flu grain Koran story graphic roar color replace simplicity prevalence difficulty preoccupation technology fruit faith sour laborer corner departure rape cereal stamp support sweep march aisle smart recession supply trip cooperative dragon competence prescription direction pierce powder argument crew invite polish steward cut bronze adviser chicken responsibility guitar project precision study judge valid veteran party identity bathroom basis voyage favour adopt theft volcano makeup cylinder leaflet motif hiccup heavy tin landscape wheat clay aluminium accessible basic concession hen wood convince rubbish credit pity temptation lose tropical teach video border exchange reliable pride kidney line tactic user presence fitness confusion fraction replacement load climb provoke knowledge traction desert combine jewel presentation dirty pan small self topple frozen pill bride spectrum Sunday houseplant flex touch reproduce outline snow architect ego absolute lick snail"); 

    PutString("Ceci est la derniere longue chaine de caractere, mais cette fois sans retour a la ligne donc cadeau: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam nostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges: constructio interrete. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille,consentit.Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam nostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges2: constructio interrete777. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Ceci est la dernière longue chaine de caractere, mais cette fois sans retour à la ligne donc cadeau: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam nostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges3: constructio interrete. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam n888ostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges4: constructio interrete. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.                   PAS ENCORE FINIS         Ceci est la dernière longue chaine de caractere, mais cette fois sans retour à la ligne donc cadeau: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam nostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges: constructio interrete. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille,consentit.Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam nostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges2: constructio interrete777. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Ceci est la dernière longue chaine de caractere, mais cette fois sans retour à la ligne donc cadeau: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam nostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges3: constructio interrete. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.Lorem ipsum dolor sit amet, consectetur adipiscing elit. Non quam n888ostram quidem, inquit Pomponius iocans; Hunc vos beatum; Quid de Pythagora? Id mihi magnum videtur. Si quicquam extra virtutem habeatur in bonis. Age, inquies, ista parva sunt. Duo Reges4: constructio interrete. Tum Torquatus: Prorsus, inquit, assentior;Sullae consulatum? Sed ad bona praeterita redeamus. Immo videri fortasse. Explanetur igitur. Esse enim, nisi eris, non potes. Minime vero, inquit ille, consentit.                   FINN\n\0");

    PutString("\n\0");
}