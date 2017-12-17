/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 16, 2017 
 */

#include <traits/traits.h>
#include <features/feature_mutable.h>
#include <kit/collections/string.h>

#define I(x)    ImmutableOption_unwrap((x))

struct Seed {
    const char *SUT;
    const size_t SUT_SIZE;
    const char *OTHER;
    const size_t OTHER_SIZE;
    const char *UNION;
    const size_t UNION_SIZE;
};

const struct Seed LITERAL_SEEDS[] = {
        {.SUT="", .SUT_SIZE=0, .OTHER="", .OTHER_SIZE=0, .UNION="", .UNION_SIZE=0},
        {.SUT="", .SUT_SIZE=0, .OTHER="NQmTQ\a\bL\ruhzu\b\rVUuPSrOpmz\noSnl\"\nsQHpTMIG\b\"siGqRNtuVSnIOpVpRMOor", .OTHER_SIZE=63, .UNION="NQmTQ\a\bL\ruhzu\b\rVUuPSrOpmz\noSnl\"\nsQHpTMIG\b\"siGqRNtuVSnIOpVpRMOor", .UNION_SIZE=63},
        {.SUT="", .SUT_SIZE=0, .OTHER="VUNzpoUtUM\tORTQ\rq\tl\rPHi\a\"\b\tNlVItPqH\tsUULuoL\bnUSimQLHM\nnU\tzQz\"qzh\tMnTHSn\a\"LGqmvzLS\rz\bvVsRGr\aOHnIom\r\a\r\thUS\bnLslRQPnZ\tSigVTGvuIUgZs\bNm\bU\bnpNnHvr\"vO\r\aGmUHoMmV\n\"NipsIiP\bONzvvznNtQMPLQvzG\t\"\tZq\tvrpuq\tLNLOgNLLPVlRQZT\rvp\rvqNmn\aVT\b\nHzz\bNrn", .OTHER_SIZE=229, .UNION="VUNzpoUtUM\tORTQ\rq\tl\rPHi\a\"\b\tNlVItPqH\tsUULuoL\bnUSimQLHM\nnU\tzQz\"qzh\tMnTHSn\a\"LGqmvzLS\rz\bvVsRGr\aOHnIom\r\a\r\thUS\bnLslRQPnZ\tSigVTGvuIUgZs\bNm\bU\bnpNnHvr\"vO\r\aGmUHoMmV\n\"NipsIiP\bONzvvznNtQMPLQvzG\t\"\tZq\tvrpuq\tLNLOgNLLPVlRQZT\rvp\rvqNmn\aVT\b\nHzz\bNrn", .UNION_SIZE=229},
        {.SUT="\a\rIOuHgvUST\azVTiITOVtMoQnNuVOqZ\nMmsRHrqoQmTllupnII\bszhlmnlL", .SUT_SIZE=59, .OTHER="", .OTHER_SIZE=0, .UNION="\a\rIOuHgvUST\azVTiITOVtMoQnNuVOqZ\nMmsRHrqoQmTllupnII\bszhlmnlL", .UNION_SIZE=59},
        {.SUT="mooLVgN\tGUQMURnqttlGqtlOg\b\amQm\"pZpLLUpU\bZSOqvLUzhMS\avgzOhQilhmqpRM\bguNn\riGIrvsQi\rpLn\tVVUslUQ\bvqlLR\rvNupQgutHgrHSUuhHLO\a\"Lq\"hgisz\aHhLVhvPgo\aRrLzGON\nosslnTLzqqMh\a\anoloI\nhmlQRUt\aR\rRTl\aoGNPNviiuSP\ammtuOI\"\"Om\aZsligVhZMU\ttZooNqhqmrzRQGn\aosPIlvuL\ns\"n\ruVGP\n", .SUT_SIZE=249, .OTHER="", .OTHER_SIZE=0, .UNION="mooLVgN\tGUQMURnqttlGqtlOg\b\amQm\"pZpLLUpU\bZSOqvLUzhMS\avgzOhQilhmqpRM\bguNn\riGIrvsQi\rpLn\tVVUslUQ\bvqlLR\rvNupQgutHgrHSUuhHLO\a\"Lq\"hgisz\aHhLVhvPgo\aRrLzGON\nosslnTLzqqMh\a\anoloI\nhmlQRUt\aR\rRTl\aoGNPNviiuSP\ammtuOI\"\"Om\aZsligVhZMU\ttZooNqhqmrzRQGn\aosPIlvuL\ns\"n\ruVGP\n", .UNION_SIZE=249},
        {.SUT="\"uiTsNiIN\aTIvM\r\nnmHovTZVitQMm\nitUlzgs\nRHQSiNi\tOzPSqTzmTmr\t\"ZPZVgvSsgvvlnTGPOSUMTmGhvGnUoRP\a\ri\agquh\ro\n\amGzUGrGQ\bHVhzmIIthM\aZ\nt\nzVPt\n\arSo\"ghg\aPqvgv\rihPo\bvPTQM\ruqutR\b\"\r\aH\riLRzpRlThNRvltZIO", .SUT_SIZE=185, .OTHER="pGPSqHtTiHrQzHvT\"\rHmsLtTrh\anmLzuqP\noOzQ\ahU\bTnnp\bSOruNizpItlqzGVQNlmIUTzVRT\nVnrqp\t\bpIPnvtTSsrVvL\"GmNngSvRrvpM\bZZuMZsILOI\t\a\rLuM\rQOHmTIspNnV\tl\"S\"\toQq\r", .OTHER_SIZE=147, .UNION="\"uiTsNiIN\aTIvM\r\nnmHovTZVitQMm\nitUlzgs\nRHQSiNi\tOzPSqTzmTmr\t\"ZPZVgvSsgvvlnTGPOSUMTmGhvGnUoRP\a\ri\agquh\ro\n\amGzUGrGQ\bHVhzmIIthM\aZ\nt\nzVPt\n\arSo\"ghg\aPqvgv\rihPo\bvPTQM\ruqutR\b\"\r\aH\riLRzpRlThNRvltZIOpGPSqHtTiHrQzHvT\"\rHmsLtTrh\anmLzuqP\noOzQ\ahU\bTnnp\bSOruNizpItlqzGVQNlmIUTzVRT\nVnrqp\t\bpIPnvtTSsrVvL\"GmNngSvRrvpM\bZZuMZsILOI\t\a\rLuM\rQOHmTIspNnV\tl\"S\"\toQq\r", .UNION_SIZE=332},
        {.SUT="tvo\rsSmqG\nhTpTRg\ar\nU\"goIno\"qtZnSzmlqvPP\rhpgrtgOpvO\nNhRZpm\tilVZUrpVOGIv\rrzzvnuP\"uO\rVI\rUhim\b\nz\"\bVvMlSL\"rTvZLqppVs\ntMnhNSGSN", .SUT_SIZE=121, .OTHER="TgrSqussnv\rqsTIo\nLVO\bN\nhUOpt\rQHGhIhzHu\bPZz\tq\nPpIH\t", .OTHER_SIZE=50, .UNION="tvo\rsSmqG\nhTpTRg\ar\nU\"goIno\"qtZnSzmlqvPP\rhpgrtgOpvO\nNhRZpm\tilVZUrpVOGIv\rrzzvnuP\"uO\rVI\rUhim\b\nz\"\bVvMlSL\"rTvZLqppVs\ntMnhNSGSNTgrSqussnv\rqsTIo\nLVO\bN\nhUOpt\rQHGhIhzHu\bPZz\tq\nPpIH\t", .UNION_SIZE=171},
        {.SUT="ngtsHPo\rnTnRZHhss\tIGN\nqvitimH\aUnIouzQZML\trGrOgHovM\"mNnp\tLg\tgnzR\rR\nr\nmUt\bIsQT\rzRsrmoi\bH\rMgI\tvmUZ", .SUT_SIZE=95, .OTHER="\rvs\bvMVTrUu\bsg\aVzz\bz\t\t\tM\nPRiTSslhhOggLmHR\b\"Vo\nSq\bLv\bNSv\nznIU\tRgVzVNLZsGZtvVmlvi\rotPRS\nL\tunRvlVIIr\rqhrtnOMsvSq\rvT\rMLZ\"mlPMiN\"UHoS\arhZI\b\aUZhtrIhU\rZiGzRUG\"Lm\rqsSvTNINOoT\"TL\bUVtQOP\nIniri\brTig\"U\aVvUSl\niUr\bz\tvN\nnMM\"RTV\rQIz\b\r\aSmuIPiQtTRhRmzzs\bIulp\"MI\tiSi\t\t\aQSvg", .OTHER_SIZE=254, .UNION="ngtsHPo\rnTnRZHhss\tIGN\nqvitimH\aUnIouzQZML\trGrOgHovM\"mNnp\tLg\tgnzR\rR\nr\nmUt\bIsQT\rzRsrmoi\bH\rMgI\tvmUZ\rvs\bvMVTrUu\bsg\aVzz\bz\t\t\tM\nPRiTSslhhOggLmHR\b\"Vo\nSq\bLv\bNSv\nznIU\tRgVzVNLZsGZtvVmlvi\rotPRS\nL\tunRvlVIIr\rqhrtnOMsvSq\rvT\rMLZ\"mlPMiN\"UHoS\arhZI\b\aUZhtrIhU\rZiGzRUG\"Lm\rqsSvTNINOoT\"TL\bUVtQOP\nIniri\brTig\"U\aVvUSl\niUr\bz\tvN\nnMM\"RTV\rQIz\b\r\aSmuIPiQtTRhRmzzs\bIulp\"MI\tiSi\t\t\aQSvg", .UNION_SIZE=349},
        {.SUT="\nhn\rrG\"PqS\b\nqPzvuoSG\noGPvQ\bvgz\nUg\rqGvpvhRvrqPh\nU\"oGhmzHOvUQSSHTNOg\a\nVhNroho\nPMNIO\"NHpUlsI\t\tniNigqvLNlUVZIRUuZS\"\bTo\aLVThoo\n\tsV\amMhqpUGtnI\ngHnrnU\"Nh\"vL\"q\"\numthzzSMNVQlrnzpqlhzGOR\aHioUIPls\tQ\rh\t\rZOo\boNnhsi\tTrM\tZru\"TSVR", .SUT_SIZE=214, .OTHER="IZmouh\arhGoTNnnzhgsl\rPOIlTunP\bsTH\tTvLhNrsZOoOzSsOvQVprtHOiS\bRL\bHlOnuLSplpVLZ\nhzsGio\nP\bUQhZIzvHsmrI\toiqR\r\"iIR\bGvvhLR\a\rl\bnNR\"\aMIV\nRIPt\bQ\nMmoOlPQNOonMGLrSTpSzl\npGnLZMRTvqi\rZOnU\n\b\"gOg\rhRqIh\tzMmLOso\nmU\r\"UUPh\"G\aH\b", .OTHER_SIZE=207, .UNION="\nhn\rrG\"PqS\b\nqPzvuoSG\noGPvQ\bvgz\nUg\rqGvpvhRvrqPh\nU\"oGhmzHOvUQSSHTNOg\a\nVhNroho\nPMNIO\"NHpUlsI\t\tniNigqvLNlUVZIRUuZS\"\bTo\aLVThoo\n\tsV\amMhqpUGtnI\ngHnrnU\"Nh\"vL\"q\"\numthzzSMNVQlrnzpqlhzGOR\aHioUIPls\tQ\rh\t\rZOo\boNnhsi\tTrM\tZru\"TSVRIZmouh\arhGoTNnnzhgsl\rPOIlTunP\bsTH\tTvLhNrsZOoOzSsOvQVprtHOiS\bRL\bHlOnuLSplpVLZ\nhzsGio\nP\bUQhZIzvHsmrI\toiqR\r\"iIR\bGvvhLR\a\rl\bnNR\"\aMIV\nRIPt\bQ\nMmoOlPQNOonMGLrSTpSzl\npGnLZMRTvqi\rZOnU\n\b\"gOg\rhRqIh\tzMmLOso\nmU\r\"UUPh\"G\aH\b", .UNION_SIZE=421},
        {.SUT="tliznZ\nM\nGqrLHNqnZQplHhS\rTn\b\aLvsThMMimquLozTuHorZOiZ\"LoRor\buGTn\rszNIt\"OizToT\rGpVqGsItV\rllgGhMPV\bH\nGq\tVPvMrSSHoTTzq\t\atspiUUQ", .SUT_SIZE=123, .OTHER="pmTO\bQ\btTzZOzlOmtmlrRqU\tlnlSq\"\thUqmLSSh\t\arlqH\tHLhzPnRU\tG\nqs\r\tngvmVuZITOrq\brrz\b\nGmSMMg\tinozqIqvroIloHRl\tgLzRQ\bQhsOQM\ngtRIPphnIsQvssZQhQhGp", .OTHER_SIZE=137, .UNION="tliznZ\nM\nGqrLHNqnZQplHhS\rTn\b\aLvsThMMimquLozTuHorZOiZ\"LoRor\buGTn\rszNIt\"OizToT\rGpVqGsItV\rllgGhMPV\bH\nGq\tVPvMrSSHoTTzq\t\atspiUUQpmTO\bQ\btTzZOzlOmtmlrRqU\tlnlSq\"\thUqmLSSh\t\arlqH\tHLhzPnRU\tG\nqs\r\tngvmVuZITOrq\brrz\b\nGmSMMg\tinozqIqvroIloHRl\tgLzRQ\bQhsOQM\ngtRIPphnIsQvssZQhQhGp", .UNION_SIZE=260},
        {.SUT="rhoU\bHUls\rnOq\trgL\aILpZV\bll\"Z\rNoLomUGHoVI\bpPnU\tgmS", .SUT_SIZE=49, .OTHER="\rtqZmlNlouPizSms\tSr\tNNPg\bUiOMnouHRVUi\b\rs\t\nptumQlHLpp\tLiNQiNnovM\tQo\n\tgINNttSNNVvIsgNSVgVV\aMlnPu\bnHqgrVs\tphVLlh\b\"\rgVGgGmS\ngtnRh\bMQmlsqnPPpQo\"shuT\tlumsSnISZz\buMZrphgh\rNISpLzQIVGQpL\b\tRHoIsgLMviuPisZp\nlP\rNiQPuuv\nvv\a\"T\"\"PTSGTrVnLrTVsrvVLsi\nIRsT\an\tTITLOu\rN", .OTHER_SIZE=249, .UNION="rhoU\bHUls\rnOq\trgL\aILpZV\bll\"Z\rNoLomUGHoVI\bpPnU\tgmS\rtqZmlNlouPizSms\tSr\tNNPg\bUiOMnouHRVUi\b\rs\t\nptumQlHLpp\tLiNQiNnovM\tQo\n\tgINNttSNNVvIsgNSVgVV\aMlnPu\bnHqgrVs\tphVLlh\b\"\rgVGgGmS\ngtnRh\bMQmlsqnPPpQo\"shuT\tlumsSnISZz\buMZrphgh\rNISpLzQIVGQpL\b\tRHoIsgLMviuPisZp\nlP\rNiQPuuv\nvv\a\"T\"\"PTSGTrVnLrTVsrvVLsi\nIRsT\an\tTITLOu\rN", .UNION_SIZE=298},
        {.SUT="\tSir\t\t\rtLZUM\rGgg\rhmI\bMNiNUtQq\aRhNhQGNN\aPgQ\n", .SUT_SIZE=43, .OTHER="LT\rpOPlLPoL\"Q\rT\bQh\aP\aGHVRgiinpzGzZORori\tUzU\a\tUuolPLLTPrOisvhgPM\"pu\aVQuGZ", .OTHER_SIZE=72, .UNION="\tSir\t\t\rtLZUM\rGgg\rhmI\bMNiNUtQq\aRhNhQGNN\aPgQ\nLT\rpOPlLPoL\"Q\rT\bQh\aP\aGHVRgiinpzGzZORori\tUzU\a\tUuolPLLTPrOisvhgPM\"pu\aVQuGZ", .UNION_SIZE=115},
        {.SUT="LN\rgz\nMnqQHMpuhOztvNhP\bvgmispMTgnGmThigqRHnGmlpS\aIQnsNNTSlmsRU\r\nM\"v\aISp\tPh\rzL\amRo\n\tPtHtOiQPNSrPNvrzM\bOuzMsOozqZHtHMMZ\t\tlQ\tTpGiNMhm", .SUT_SIZE=130, .OTHER="\"MvSmMmoZVm\rHvzZ\nsoGOmhhTluUMIvT\r\tqPMGgzR\nqUzivG\nShTLIhS\"LqnntI\"\aZZULggGM\boTvMiSURun\n\"tG\tgG\bzH\trpZg\"r", .OTHER_SIZE=101, .UNION="LN\rgz\nMnqQHMpuhOztvNhP\bvgmispMTgnGmThigqRHnGmlpS\aIQnsNNTSlmsRU\r\nM\"v\aISp\tPh\rzL\amRo\n\tPtHtOiQPNSrPNvrzM\bOuzMsOozqZHtHMMZ\t\tlQ\tTpGiNMhm\"MvSmMmoZVm\rHvzZ\nsoGOmhhTluUMIvT\r\tqPMGgzR\nqUzivG\nShTLIhS\"LqnntI\"\aZZULggGM\boTvMiSURun\n\"tG\tgG\bzH\trpZg\"r", .UNION_SIZE=231},
        {.SUT="NizuutzqVm\t\t\"nuULzGON\n\rgh\tOUi\tnNpRMhhosopnz\bR\nPnNOGrIOmuP\"uQHHPh\bgI\bLlOLQ\tgG\a\a\agV\bth\nUrsSoQg\bOsosPIsvV\bHONMMUtHhr\rsIQ\rHuiImGoVtnGp\b\avqpnv", .SUT_SIZE=137, .OTHER="vH\nLOI\agL\bz\b\bUhQO\ngusmVs\boUoh\bUSzmUsth\aoqvQpGl\npgigtmq\bOnRuUSlm\rz\alVhUgZM\nm", .OTHER_SIZE=75, .UNION="NizuutzqVm\t\t\"nuULzGON\n\rgh\tOUi\tnNpRMhhosopnz\bR\nPnNOGrIOmuP\"uQHHPh\bgI\bLlOLQ\tgG\a\a\agV\bth\nUrsSoQg\bOsosPIsvV\bHONMMUtHhr\rsIQ\rHuiImGoVtnGp\b\avqpnvvH\nLOI\agL\bz\b\bUhQO\ngusmVs\boUoh\bUSzmUsth\aoqvQpGl\npgigtmq\bOnRuUSlm\rz\alVhUgZM\nm", .UNION_SIZE=212},
        {.SUT="LzM\tt\tzhNmi\a\bGqLPMTpSSILHtTsLh\tilZSs\aLZhqQnR\rNQSIvRVo\"Hl\tHNq\n\tsiVn\nn\nSounglIOGpmOPQNLi\rGoLLvlNO\bQ\tRlNtRlGHUqUsVGlSLQGipOrpHHNNqR\tLO\a\nHqlPmZtQVTptS\bzl\a\rVLigOvSOMm\nzGpT\tZQq", .SUT_SIZE=170, .OTHER="v\"uIvsT\"iziQ\ah\aUotMnLLvrOnSMulp\nuzttGl\"\tMSni\n\rLNZMLmSh\"zLOhHVRphQghlNmQL\"", .OTHER_SIZE=73, .UNION="LzM\tt\tzhNmi\a\bGqLPMTpSSILHtTsLh\tilZSs\aLZhqQnR\rNQSIvRVo\"Hl\tHNq\n\tsiVn\nn\nSounglIOGpmOPQNLi\rGoLLvlNO\bQ\tRlNtRlGHUqUsVGlSLQGipOrpHHNNqR\tLO\a\nHqlPmZtQVTptS\bzl\a\rVLigOvSOMm\nzGpT\tZQqv\"uIvsT\"iziQ\ah\aUotMnLLvrOnSMulp\nuzttGl\"\tMSni\n\rLNZMLmSh\"zLOhHVRphQghlNmQL\"", .UNION_SIZE=243},
        {.SUT="GlSpHQ\tq\n\tQUPvNzQhTrLO\tTNnrTUUIQoZvPn\n\"ohvG\nlSooHohrPssgm", .SUT_SIZE=57, .OTHER="iLnlIszlQrQvi\"uilO\nsSZ\nLiZRhH\angUnsGnPtQphgvgUuU\"ttR\rgRMLVoNNPQPq\nSiRNMHzU\tzgOvuO\nTOgUqGPIiglMVM\a\"hI\"irUuM\rsGUUPgRImguNUNv\"qO\nqpG\t\tvI\"IM\bQ\n\rTlGpnQHomSQN\tVssIpn", .OTHER_SIZE=159, .UNION="GlSpHQ\tq\n\tQUPvNzQhTrLO\tTNnrTUUIQoZvPn\n\"ohvG\nlSooHohrPssgmiLnlIszlQrQvi\"uilO\nsSZ\nLiZRhH\angUnsGnPtQphgvgUuU\"ttR\rgRMLVoNNPQPq\nSiRNMHzU\tzgOvuO\nTOgUqGPIiglMVM\a\"hI\"irUuM\rsGUUPgRImguNUNv\"qO\nqpG\t\tvI\"IM\bQ\n\rTlGpnQHomSQN\tVssIpn", .UNION_SIZE=216},
        {.SUT="przGP\"tSomGiuPIu\rh\"v\t\r\aUoRGpSP\nTtZiHGQ\b\r\arLRHUpZ\aonzH\buUThm\n", .SUT_SIZE=60, .OTHER="RzRLPpqNTUs\"pnphpuhZ\rQvHT\biIsuRtQL\nq\ttMqLggZhoPH\"pplhhl\thNI\ttLirmH\rstuIt\av\"ZUVst\bmS\tZMh\"lz\rQtONgt\apoqzsSvr\rSGuOSPqmtSSUzHVQpigTtl\riStrtlvvgg", .OTHER_SIZE=140, .UNION="przGP\"tSomGiuPIu\rh\"v\t\r\aUoRGpSP\nTtZiHGQ\b\r\arLRHUpZ\aonzH\buUThm\nRzRLPpqNTUs\"pnphpuhZ\rQvHT\biIsuRtQL\nq\ttMqLggZhoPH\"pplhhl\thNI\ttLirmH\rstuIt\av\"ZUVst\bmS\tZMh\"lz\rQtONgt\apoqzsSvr\rSGuOSPqmtSSUzHVQpigTtl\riStrtlvvgg", .UNION_SIZE=200},
        {.SUT="TiItIvZ\riqqpv\"pgipVn\"M\nO\rh\nl\aLLzoHTMzpmRMGqLuG\nRqi\rvZZ\tz", .SUT_SIZE=56, .OTHER="nulMUgNmOLzNI\r\"Rroz\tTiZrpLN\tpq\tMHoHinMGoqto\rRR\bNIuNnMpslSZTtIungHnLloHIRqllmMMoqHUr\nSH\"\bRhVhzGszOnnO\aVVVNgHmM\rqo\aP\buMRLSSzUIIrSIsLLqM\nlgurvVQV\nVgv\b\tiVhii\"QznOnz\r\bNOP\b\avgP\rMIl\"toMQTiim\nZLo\tzQr\rZOTO\bTnn\t\tSZhZHznONHqg\tIo\n\a\bhSlHLv\nZvO\alqZOptrn", .OTHER_SIZE=239, .UNION="TiItIvZ\riqqpv\"pgipVn\"M\nO\rh\nl\aLLzoHTMzpmRMGqLuG\nRqi\rvZZ\tznulMUgNmOLzNI\r\"Rroz\tTiZrpLN\tpq\tMHoHinMGoqto\rRR\bNIuNnMpslSZTtIungHnLloHIRqllmMMoqHUr\nSH\"\bRhVhzGszOnnO\aVVVNgHmM\rqo\aP\buMRLSSzUIIrSIsLLqM\nlgurvVQV\nVgv\b\tiVhii\"QznOnz\r\bNOP\b\avgP\rMIl\"toMQTiim\nZLo\tzQr\rZOTO\bTnn\t\tSZhZHznONHqg\tIo\n\a\bhSlHLv\nZvO\alqZOptrn", .UNION_SIZE=295},
        {.SUT="gOVUurzQ\"NvihiVuTz\bT\tlGgNuTVoz\npLIiQnR\bi\nsmG\tsmrv\np\a\t\"mlZzlVTq\az\brqTv\tlnRrzGqTotV\"tGg\tV\b\rISI\b\tgMq\b\"\ruOH\rGrpmNMn\r\bOqVMm\t\"HVMqz\rLml\bTLPrGgG\nvvOUgGi\"mZuolGGzGghmT\tR\"Tt\a\noPpGVISzO\anZGm\aQ\"ZN\nSMZ\"pTsnGMQSuzHHiSMRHzOL", .SUT_SIZE=210, .OTHER="nu\a\bmzRlRshzSpQmgHRmmgqzr\aMoHZn\aiMMuLGRMTonqG\ngip\nv\tmrivL\nlUL\bVlnz\rNIO\"mQuNlZvnM\"zHVzth\"\nNQii\"ln\aRNZg\tlV\"pmhOqnPiPLgSVo\rmOgnHvOQpPnV\nQRT\aUMppLsZNPuTpIti\bIT\bPHlNvp\apipN\rNn\tMOZN\rmzZPHn", .OTHER_SIZE=182, .UNION="gOVUurzQ\"NvihiVuTz\bT\tlGgNuTVoz\npLIiQnR\bi\nsmG\tsmrv\np\a\t\"mlZzlVTq\az\brqTv\tlnRrzGqTotV\"tGg\tV\b\rISI\b\tgMq\b\"\ruOH\rGrpmNMn\r\bOqVMm\t\"HVMqz\rLml\bTLPrGgG\nvvOUgGi\"mZuolGGzGghmT\tR\"Tt\a\noPpGVISzO\anZGm\aQ\"ZN\nSMZ\"pTsnGMQSuzHHiSMRHzOLnu\a\bmzRlRshzSpQmgHRmmgqzr\aMoHZn\aiMMuLGRMTonqG\ngip\nv\tmrivL\nlUL\bVlnz\rNIO\"mQuNlZvnM\"zHVzth\"\nNQii\"ln\aRNZg\tlV\"pmhOqnPiPLgSVo\rmOgnHvOQpPnV\nQRT\aUMppLsZNPuTpIti\bIT\bPHlNvp\apipN\rNn\tMOZN\rmzZPHn", .UNION_SIZE=392},
        {.SUT="TRRs\tN\aG\aggsmvvVihzTQsGGZtV\tIztzosLU\"tvvUMoSLqMNUo\"mUtrMon\aNVpvvTpVLnR\aToioRZuQIzqlV", .SUT_SIZE=84, .OTHER="um\"n\"sNmO\a\aU\aVnqiLz\rHqH\aSthZ\"Z\b\bn\"pmtVSI\bmUTmvszZPhq\bItohPMgpIzpSsiSz\b\riOzphVmvp\bHZuRVOtoomvrM\bMQIUOZuPrgihVrLOri\n\nhvzmP\tiQZVROiOzQUpTSnNgqtssONLPQVuTuQOQShmZZVnH\"nuTliIIlMPtH\b\nss\tZtu\aQRi\bOThqRNhSzsPzqmgr\rRlzhrSih\rzPHv", .OTHER_SIZE=218, .UNION="TRRs\tN\aG\aggsmvvVihzTQsGGZtV\tIztzosLU\"tvvUMoSLqMNUo\"mUtrMon\aNVpvvTpVLnR\aToioRZuQIzqlVum\"n\"sNmO\a\aU\aVnqiLz\rHqH\aSthZ\"Z\b\bn\"pmtVSI\bmUTmvszZPhq\bItohPMgpIzpSsiSz\b\riOzphVmvp\bHZuRVOtoomvrM\bMQIUOZuPrgihVrLOri\n\nhvzmP\tiQZVROiOzQUpTSnNgqtssONLPQVuTuQOQShmZZVnH\"nuTliIIlMPtH\b\nss\tZtu\aQRi\bOThqRNhSzsPzqmgr\rRlzhrSih\rzPHv", .UNION_SIZE=302},
        {.SUT="\rSVpm\"phOHgoUNmz\rNillt\ntSrqHGPimpgQMLsZ\t\aiG\tNR\t\"OonHiz\bZHMV\rinHT\"LGuS\rZghLZv\t\bPGO\bsUzOLHoRNzIg\aVtrQQIrzIMzRn\"mZTO\rVR\rl\"rZ\bqMv\"i\"itS\ttIGpgTtQnhIrHSpzvII\bTtOUThn\b\aU\r\rHpMzSouupo\b\nGomq\rGIqMQv\t\"\"\"q\b\aNH\"SgiQH\bGOzH", .SUT_SIZE=207, .OTHER="IsSRLP\aprURgHOMUMih\"o\rzGurhQpnsqTiIQmoS\a\brz\bTrrpnsrZZMt\atpLRL\tiSPv\tuzRQitORQUp\nGQpIUm\alI\"o\biQh\tnp\avMt\azghzz\tIUqrioTMssTitRLP\nsZVtZH\a\nUOuIOQpTsRO\aIl\bRnorUvrssP\tgLvt\tGvR\r\r\b\toRvuPPnzIH\roNul\"ruOgZMzRRNMVqIGt\tHIm\rshtIvo\"iqI\"ttpZuRqPogsZ\bZu\nlMguNSn\brTz\a\rP\a\aooG", .OTHER_SIZE=254, .UNION="\rSVpm\"phOHgoUNmz\rNillt\ntSrqHGPimpgQMLsZ\t\aiG\tNR\t\"OonHiz\bZHMV\rinHT\"LGuS\rZghLZv\t\bPGO\bsUzOLHoRNzIg\aVtrQQIrzIMzRn\"mZTO\rVR\rl\"rZ\bqMv\"i\"itS\ttIGpgTtQnhIrHSpzvII\bTtOUThn\b\aU\r\rHpMzSouupo\b\nGomq\rGIqMQv\t\"\"\"q\b\aNH\"SgiQH\bGOzHIsSRLP\aprURgHOMUMih\"o\rzGurhQpnsqTiIQmoS\a\brz\bTrrpnsrZZMt\atpLRL\tiSPv\tuzRQitORQUp\nGQpIUm\alI\"o\biQh\tnp\avMt\azghzz\tIUqrioTMssTitRLP\nsZVtZH\a\nUOuIOQpTsRO\aIl\bRnorUvrssP\tgLvt\tGvR\r\r\b\toRvuPPnzIH\roNul\"ruOgZMzRRNMVqIGt\tHIm\rshtIvo\"iqI\"ttpZuRqPogsZ\bZu\nlMguNSn\brTz\a\rP\a\aooG", .UNION_SIZE=461},
};

const size_t LITERAL_SEEDS_SIZE = sizeof(LITERAL_SEEDS) / sizeof(LITERAL_SEEDS[0]);

const struct Seed BYTES_SEEDS[] = {
        {.SUT="", .SUT_SIZE=0, .OTHER="", .OTHER_SIZE=0, .UNION="", .UNION_SIZE=0},
        {.SUT="", .SUT_SIZE=0, .OTHER="IQlPP\"m\nL\aVovp\amTMLGISpzq\"UZnRZiSvUVQil", .OTHER_SIZE=39, .UNION="IQlPP\"m\nL\aVovp\amTMLGISpzq\"UZnRZiSvUVQil", .UNION_SIZE=39},
        {.SUT="", .SUT_SIZE=0, .OTHER="uqlVO\tm\"LOrzZPmNviN\"guSmVipzgunmtTLnm\n\x00hTLHu\noZl\t\toihnHnRRzM\autUOq\bvSM\"\rv\x00TNRn\n\t\"\x00VtLHL\a\nT\ruiMI\bL\"v\x00\bMnQtgSQ\tuHpqZhIS\nHNmRIS\bQo\a\tiH\x00toQ\r\t\nS\x00uuPzNorpGV\aoSqpI\nu\aOzmZ\bH\t\b\nl\x00otO\bPHP\"\"It\x00vT", .OTHER_SIZE=184, .UNION="uqlVO\tm\"LOrzZPmNviN\"guSmVipzgunmtTLnm\n\x00hTLHu\noZl\t\toihnHnRRzM\autUOq\bvSM\"\rv\x00TNRn\n\t\"\x00VtLHL\a\nT\ruiMI\bL\"v\x00\bMnQtgSQ\tuHpqZhIS\nHNmRIS\bQo\a\tiH\x00toQ\r\t\nS\x00uuPzNorpGV\aoSqpI\nu\aOzmZ\bH\t\b\nl\x00otO\bPHP\"\"It\x00vT", .UNION_SIZE=184},
        {.SUT="MIpmqusmnV\bN\"isiHuV\n\rvGtGtl\rqQ\rn\niu\nrHQurs\x00QIGNnNMqHpqtV\bI\r", .SUT_SIZE=59, .OTHER="", .OTHER_SIZE=0, .UNION="MIpmqusmnV\bN\"isiHuV\n\rvGtGtl\rqQ\rn\niu\nrHQurs\x00QIGNnNMqHpqtV\bI\r", .UNION_SIZE=59},
        {.SUT="\x00V\x00\b\nlqI\tgVoq\x00uNgqRrG\nzOLPZRLssh\tooGiHvUQopZLrim\x00\bIglQzSI\b\t\aQLQgzHiIqmZMnhunUriqur\tOZTzQUSvP\"iMOvVsOQph\aN\t\bN\rQllslTsRtloRHgq\bI\x00\x00\rgOp\rsh\"osZhm\bg\aqmGvIPmv\a\tzossHRi\auHR\"\tSoOLRHptPTmP\n\x00\nNV\nNRIMroHlVt\bvNnv\x00OOoMSL\bSR\x00\r", .SUT_SIZE=212, .OTHER="", .OTHER_SIZE=0, .UNION="\x00V\x00\b\nlqI\tgVoq\x00uNgqRrG\nzOLPZRLssh\tooGiHvUQopZLrim\x00\bIglQzSI\b\t\aQLQgzHiIqmZMnhunUriqur\tOZTzQUSvP\"iMOvVsOQph\aN\t\bN\rQllslTsRtloRHgq\bI\x00\x00\rgOp\rsh\"osZhm\bg\aqmGvIPmv\a\tzossHRi\auHR\"\tSoOLRHptPTmP\n\x00\nNV\nNRIMroHlVt\bvNnv\x00OOoMSL\bSR\x00\r", .UNION_SIZE=212},
        {.SUT="Nlg\rGlRU\x00ihzu\"mPzp\"H\bhzs\x00hv\nT\"rIghHhLOqTuuirUlpoz\"\rUPS\bmvHPuL\a\bVRUVhZSNu\t\rsqPGhUSPvhuNmQoVMU\x00QLqvZllnGuOq\tvGLrTqg\"\r\nosTSGigSrM\rPzumMvsUIuusR\bzruv\nSiSHMNUQNm\rpIvM\aismz\tGII\"\aM\r\noqrTTuIZlnRUTrhS\"NGGMqo\rlVolQgg\r\n", .SUT_SIZE=208, .OTHER="nmLIhuzRU\nNn\x00tstr\x00ns\trNNzNszOpp\bZMvNi\brP\n\bhovQZgQTO\"Iu\tITNmlmmtonvUOlNLSSU\tr\bZZLs\"sVvgnVUQslql", .OTHER_SIZE=94, .UNION="Nlg\rGlRU\x00ihzu\"mPzp\"H\bhzs\x00hv\nT\"rIghHhLOqTuuirUlpoz\"\rUPS\bmvHPuL\a\bVRUVhZSNu\t\rsqPGhUSPvhuNmQoVMU\x00QLqvZllnGuOq\tvGLrTqg\"\r\nosTSGigSrM\rPzumMvsUIuusR\bzruv\nSiSHMNUQNm\rpIvM\aismz\tGII\"\aM\r\noqrTTuIZlnRUTrhS\"NGGMqo\rlVolQgg\r\nnmLIhuzRU\nNn\x00tstr\x00ns\trNNzNszOpp\bZMvNi\brP\n\bhovQZgQTO\"Iu\tITNmlmmtonvUOlNLSSU\tr\bZZLs\"sVvgnVUQslql", .UNION_SIZE=302},
        {.SUT="NzZsipiNPNzQ\x00LU\"It\x00RrLhT\"Zz\rGTOmo\nRPMzPMsZTRqrNMRZrpzsmIgG\aZM\aRoIOolGl\nUTIVG\b\"zn\r\"sIn\nllrvzQPUULuPmt\n\"OHUUuq\"s\bvLGZQVp\biUtzPvS\n\"Ss\x00\bPz\r\nmqiQL\am\x00tZugNzr\nQlptIVP\x00ZHN\rRi\"\tTIvpLUvT\n\nPvgoQntSur\"TiQUUNv\arTOH\x00gs\aI\aPs\aUrZIUuSLhzm\nt\ahsshUHqRN\x00Mqh\tQ\bTP\"Qm\x00TUo\nIin", .SUT_SIZE=253, .OTHER="mpN\x00Mi\nLhuGpL\ans\"RoZ\x00Gm\x00\bP\a\tpO\bh\tPqtQhzilzGHhO\rvLvQ\anu\bnvROZR\bLpq\rrTQqNQrp\agzZm\tIuSs\x00VMus\"gOhTHUNnrTllu\x00tUqmh\nI\x00thpV\"\rv\nRSZ\aMSM\ti\"\atPn\"\r\"iptGrl\"i\nilN\nQmOhqI\aGVSiOSl\nGNTHovLPL\bqgUIiVUnnI\brlL", .OTHER_SIZE=189, .UNION="NzZsipiNPNzQ\x00LU\"It\x00RrLhT\"Zz\rGTOmo\nRPMzPMsZTRqrNMRZrpzsmIgG\aZM\aRoIOolGl\nUTIVG\b\"zn\r\"sIn\nllrvzQPUULuPmt\n\"OHUUuq\"s\bvLGZQVp\biUtzPvS\n\"Ss\x00\bPz\r\nmqiQL\am\x00tZugNzr\nQlptIVP\x00ZHN\rRi\"\tTIvpLUvT\n\nPvgoQntSur\"TiQUUNv\arTOH\x00gs\aI\aPs\aUrZIUuSLhzm\nt\ahsshUHqRN\x00Mqh\tQ\bTP\"Qm\x00TUo\nIinmpN\x00Mi\nLhuGpL\ans\"RoZ\x00Gm\x00\bP\a\tpO\bh\tPqtQhzilzGHhO\rvLvQ\anu\bnvROZR\bLpq\rrTQqNQrp\agzZm\tIuSs\x00VMus\"gOhTHUNnrTllu\x00tUqmh\nI\x00thpV\"\rv\nRSZ\aMSM\ti\"\atPn\"\r\"iptGrl\"i\nilN\nQmOhqI\aGVSiOSl\nGNTHovLPL\bqgUIiVUnnI\brlL", .UNION_SIZE=442},
        {.SUT="v\x00\bq\rlINUNG\aOz\x00iNNTTI\asVhu\rVUPuTg\aOrNQhq\t\aq\tvPmoioqsglsIhIGUgMNqghSITq\"", .SUT_SIZE=71, .OTHER="qnSS\rqqPviS\x00\x00IhIsGolO\tnR\x00\nOISnpHHsOStZZQmu", .OTHER_SIZE=42, .UNION="v\x00\bq\rlINUNG\aOz\x00iNNTTI\asVhu\rVUPuTg\aOrNQhq\t\aq\tvPmoioqsglsIhIGUgMNqghSITq\"qnSS\rqqPviS\x00\x00IhIsGolO\tnR\x00\nOISnpHHsOStZZQmu", .UNION_SIZE=113},
        {.SUT="RpiNuho\a\t\x00\"r\n\"HQVZovhHQSnPSZ\rLgTgG\rl\"\"IpHsMPgs\rs\rhZO\tiqho\rsquuGP\tIuzvQIUNROVl\anmZ\"sgNZZmqgr\r\"\x00LmNt\a\aIlh\x00\bNrU\rZGNU\bHuHvv\ats\aM\bt\aN\bGZn\tN\x00uRio\bGro\x00\tumzNGVRMvLgpvS\agZUN\tOUH\t\x00\rqRQnVl\azmGM\x00hGnIQR\r\bm\bZvrMQQp\rS\tOMrighGISPImhL\"\rq\aG\a\ngGns\x00\aSPrU\x00O\x00MgligrR", .SUT_SIZE=244, .OTHER="S\rQLnQNN\bhHtNluNsi\bRoOt\n\rlsuls\rlImUU", .OTHER_SIZE=36, .UNION="RpiNuho\a\t\x00\"r\n\"HQVZovhHQSnPSZ\rLgTgG\rl\"\"IpHsMPgs\rs\rhZO\tiqho\rsquuGP\tIuzvQIUNROVl\anmZ\"sgNZZmqgr\r\"\x00LmNt\a\aIlh\x00\bNrU\rZGNU\bHuHvv\ats\aM\bt\aN\bGZn\tN\x00uRio\bGro\x00\tumzNGVRMvLgpvS\agZUN\tOUH\t\x00\rqRQnVl\azmGM\x00hGnIQR\r\bm\bZvrMQQp\rS\tOMrighGISPImhL\"\rq\aG\a\ngGns\x00\aSPrU\x00O\x00MgligrRS\rQLnQNN\bhHtNluNsi\bRoOt\n\rlsuls\rlImUU", .UNION_SIZE=280},
        {.SUT="TnNLhQIuhn\x00IpNG\rg\a\a\"vSqnmZZH\rIIqptg\tLHNrs\x00PUHVPQur\r\rT\rVOn\arlSTV\x00\bL\tGth", .SUT_SIZE=70, .OTHER="VZ\tpUm\tO\bQnTN\bS\rPngnZoZPIQHLHvHGpR\bGM\nL\nVqI\x00n\"tzShoMv\btsRm\t\nMQI\aS\"LTH", .OTHER_SIZE=69, .UNION="TnNLhQIuhn\x00IpNG\rg\a\a\"vSqnmZZH\rIIqptg\tLHNrs\x00PUHVPQur\r\rT\rVOn\arlSTV\x00\bL\tGthVZ\tpUm\tO\bQnTN\bS\rPngnZoZPIQHLHvHGpR\bGM\nL\nVqI\x00n\"tzShoMv\btsRm\t\nMQI\aS\"LTH", .UNION_SIZE=139},
        {.SUT="oZQ\bh\rimLuU\nmrvNmng\ngrN\rNSLnZshzzuZLIH\aIut\x00ormZQ\rUL\n\"\tRQ\ttPn\bZ\rRsgMo\bZm\bUMLT\"\x00NLvsoRIOUsrit\amM\tI\"UOq\"g\bI\noLMvSs\rtn\a\nTv\b\tNvrt\t\t\rgQRGGPuNHv\"ummuOhUQuVTg\aLuHZpzg\"OGNsMm\b\tttIp\rGM\x00pl\aPHrr\n\nruSmsThvG\"ti", .SUT_SIZE=196, .OTHER="PN\bVIoINz\a\nlu\arOmM\rSqLzo\"oh\x00roq\nmvSVOVR\rquprt\r\bvtVVp\nOItTopvnIg\x00\bgNriG\aU\t\r\tIzPuUVruRZuTTGuNVUMvLt\r\bq\tNLZNq\ah\bg\bhVMMhoVS\bZQtNR\nPro\toLu\bVIZNr\t\no\b", .OTHER_SIZE=143, .UNION="oZQ\bh\rimLuU\nmrvNmng\ngrN\rNSLnZshzzuZLIH\aIut\x00ormZQ\rUL\n\"\tRQ\ttPn\bZ\rRsgMo\bZm\bUMLT\"\x00NLvsoRIOUsrit\amM\tI\"UOq\"g\bI\noLMvSs\rtn\a\nTv\b\tNvrt\t\t\rgQRGGPuNHv\"ummuOhUQuVTg\aLuHZpzg\"OGNsMm\b\tttIp\rGM\x00pl\aPHrr\n\nruSmsThvG\"tiPN\bVIoINz\a\nlu\arOmM\rSqLzo\"oh\x00roq\nmvSVOVR\rquprt\r\bvtVVp\nOItTopvnIg\x00\bgNriG\aU\t\r\tIzPuUVruRZuTTGuNVUMvLt\r\bq\tNLZNq\ah\bg\bhVMMhoVS\bZQtNR\nPro\toLu\bVIZNr\t\no\b", .UNION_SIZE=339},
        {.SUT="UrLmzs\aQmiRTrPP\bst\rhlh\x00t\tGPMnhLnZSZ\nzSNtl\nhiMm\tRqnzUGViZp\tm\"SOpHulumHVNZR\tvhqHVgTPZ\rZN\b\bR\"SPniRZgILshLpRRQ\"vghUqmtShGTRhH\brvn\tNmZpiTPt\ahZpiQOPHisotnNi\tRohHvSIv\t\rOmMH\nV\rTShrsnHMQrgUG\n\btt\rgqLQU\t\b\x00tlTGH\bOt", .SUT_SIZE=202, .OTHER="tzMlZHGzQiULuMlPZrN\thhNnpIHqO\nNQM\rzV\"HVgtgto", .OTHER_SIZE=44, .UNION="UrLmzs\aQmiRTrPP\bst\rhlh\x00t\tGPMnhLnZSZ\nzSNtl\nhiMm\tRqnzUGViZp\tm\"SOpHulumHVNZR\tvhqHVgTPZ\rZN\b\bR\"SPniRZgILshLpRRQ\"vghUqmtShGTRhH\brvn\tNmZpiTPt\ahZpiQOPHisotnNi\tRohHvSIv\t\rOmMH\nV\rTShrsnHMQrgUG\n\btt\rgqLQU\t\b\x00tlTGH\bOttzMlZHGzQiULuMlPZrN\thhNnpIHqO\nNQM\rzV\"HVgtgto", .UNION_SIZE=246},
        {.SUT="Sl\x00z\b\n\aORlPUSzGPitQvLLn\x00gRrn\"nqUVuT\a\roSvtIOMQM\"\a\aOT\"N\toVzTLN\"QOopGLIMRihu\boThOZ\tlLvM\"TpmL\t\bnNhPltZR\x00qtLHvN\"Ll\rq\aM\bPnHlhnIpIH\"HvS\bzR\tmTMh\trzUN\aT\b\aHLGTS\thh\bH", .SUT_SIZE=155, .OTHER="Qgo\bmh\aHTqmS\buqOO\bUOQ\rprHh\"gnZV\nL\bQhrnIlLhhVnohGOQUS\tQLtH\b\tRvp\aZzmgP\b\x00oH", .OTHER_SIZE=72, .UNION="Sl\x00z\b\n\aORlPUSzGPitQvLLn\x00gRrn\"nqUVuT\a\roSvtIOMQM\"\a\aOT\"N\toVzTLN\"QOopGLIMRihu\boThOZ\tlLvM\"TpmL\t\bnNhPltZR\x00qtLHvN\"Ll\rq\aM\bPnHlhnIpIH\"HvS\bzR\tmTMh\trzUN\aT\b\aHLGTS\thh\bHQgo\bmh\aHTqmS\buqOO\bUOQ\rprHh\"gnZV\nL\bQhrnIlLhhVnohGOQUS\tQLtH\b\tRvp\aZzmgP\b\x00oH", .UNION_SIZE=227},
        {.SUT="VI\"N\r\tZh\bVMsOmSruLM\asIrQnhSooNsnHnImpTL\als\x00Qul\aROsihsGHszvRHTQLZSNs\n\to\aTRnUZIirtOQNi\"Hr\btmIrmpguIV\bgsg\nphZRspQsZ\x00\"gHS", .SUT_SIZE=117, .OTHER="\bRoVNL\a\bQOlUgoZsotLH\tGHUIsuu\rPG\tlVqmzpMmILsVvPzpiqPu\aLrVGhupRVzGITO\tOMQs\r\tvH\"mZ\"HQziUzl\bpQn\nt\a\a\bL\nHVTssT\tvMSvV\alSQilTsQpPMoZQliTNv\x00LSGv\b\nRpNH\tG\rG\x00Zmqst\atMr\x00oZ\"\tMh\bIhHLNLiN\tG\nIQMNil", .OTHER_SIZE=180, .UNION="VI\"N\r\tZh\bVMsOmSruLM\asIrQnhSooNsnHnImpTL\als\x00Qul\aROsihsGHszvRHTQLZSNs\n\to\aTRnUZIirtOQNi\"Hr\btmIrmpguIV\bgsg\nphZRspQsZ\x00\"gHS\bRoVNL\a\bQOlUgoZsotLH\tGHUIsuu\rPG\tlVqmzpMmILsVvPzpiqPu\aLrVGhupRVzGITO\tOMQs\r\tvH\"mZ\"HQziUzl\bpQn\nt\a\a\bL\nHVTssT\tvMSvV\alSQilTsQpPMoZQliTNv\x00LSGv\b\nRpNH\tG\rG\x00Zmqst\atMr\x00oZ\"\tMh\bIhHLNLiN\tG\nIQMNil", .UNION_SIZE=297},
        {.SUT="uNN\b\x00\"uvIVtrhNNqi\"u\aZsr\bTP\tn\bUgSvmPHGLMqI\nusInNPu\rRPi\aR\x00", .SUT_SIZE=56, .OTHER="PM\nolnG\r\"Umu\"\rPM\bHOzoNhHzTHp\"SNvUnhp\a\tZmngtnV\"ssz\a\asO\x00thp\rr\x00m\bplvi\"HPNR\nho\nZ\rpG\x00nqv\rhShti\bm\t\b\tM\agGPP\nIlZIHl\boQsRtmpt\alOo\aRtGSiPIr\rR\tzN\"VqOIvOvVOsp\t\tZpzqMT\x00\rin\t\x00oo\asVLunRH\aU\"\nSPuz\tRoLMn\al\x00gsGGNIpI\"L\nrR\a\rM\"OupvOTQ\agHR\aUisvuGqGp\ahZ\thgt", .OTHER_SIZE=232, .UNION="uNN\b\x00\"uvIVtrhNNqi\"u\aZsr\bTP\tn\bUgSvmPHGLMqI\nusInNPu\rRPi\aR\x00PM\nolnG\r\"Umu\"\rPM\bHOzoNhHzTHp\"SNvUnhp\a\tZmngtnV\"ssz\a\asO\x00thp\rr\x00m\bplvi\"HPNR\nho\nZ\rpG\x00nqv\rhShti\bm\t\b\tM\agGPP\nIlZIHl\boQsRtmpt\alOo\aRtGSiPIr\rR\tzN\"VqOIvOvVOsp\t\tZpzqMT\x00\rin\t\x00oo\asVLunRH\aU\"\nSPuz\tRoLMn\al\x00gsGGNIpI\"L\nrR\a\rM\"OupvOTQ\agHR\aUisvuGqGp\ahZ\thgt", .UNION_SIZE=288},
        {.SUT="\tQ\b\aTSgg\tL\tUGhtn\x00uzTgRgrLs\aiI\x00NvgTShuTs\tZGVRzMhpVzsguovp\bTRUHTPlp", .SUT_SIZE=65, .OTHER="QGqmM\rHZVSrSZVIG\x00mS\"pZnhOHLPtN\"\"O\aqhTNLQSNthtgG\x00NoO\brZmH\x00qTMsrqzugrm\"\nhQi\nUR\a\roMzhV\tNsmoqGToiNGgVhr\b\bvolhrQgV\aVIpPh\"\bPMthM\bhpvzrl", .OTHER_SIZE=129, .UNION="\tQ\b\aTSgg\tL\tUGhtn\x00uzTgRgrLs\aiI\x00NvgTShuTs\tZGVRzMhpVzsguovp\bTRUHTPlpQGqmM\rHZVSrSZVIG\x00mS\"pZnhOHLPtN\"\"O\aqhTNLQSNthtgG\x00NoO\brZmH\x00qTMsrqzugrm\"\nhQi\nUR\a\roMzhV\tNsmoqGToiNGgVhr\b\bvolhrQgV\aVIpPh\"\bPMthM\bhpvzrl", .UNION_SIZE=194},
        {.SUT="ZNmoHLzHULTQu\tugM\rgT\rhpLmIIP\"pNntnG\azupqSssTzhTs\tlggP\rtRShoLrv\"hiqq\t\t\av\r\n\tzvVMRmOhZqnNPhr", .SUT_SIZE=89, .OTHER="lmqZGQRIMSt\rRrQgpl\tl\asnsvQMLGqQ\"TvIpmtM\n\rszz\"qmp\rnuSPLztnLuNSll\tLZ\aGq\"V\x00\ruLo\bS\"pg\brRmt\bHPhv\ah\aNRgrR\x00Mu\"PhqgPUOtqq\amP\auPOMTuRIRpl\tQrpQpvziqUu\ngU\tzLiNLR\ts\rgT\x00OrNqV\n\bNgpnzs\nuoTQPUG\tUno\"Tvuvti\"QQZMML\bO\nnNLM\bgLrSNOGh\to\"n\aZhVONLpNgP\"NVrs", .OTHER_SIZE=231, .UNION="ZNmoHLzHULTQu\tugM\rgT\rhpLmIIP\"pNntnG\azupqSssTzhTs\tlggP\rtRShoLrv\"hiqq\t\t\av\r\n\tzvVMRmOhZqnNPhrlmqZGQRIMSt\rRrQgpl\tl\asnsvQMLGqQ\"TvIpmtM\n\rszz\"qmp\rnuSPLztnLuNSll\tLZ\aGq\"V\x00\ruLo\bS\"pg\brRmt\bHPhv\ah\aNRgrR\x00Mu\"PhqgPUOtqq\amP\auPOMTuRIRpl\tQrpQpvziqUu\ngU\tzLiNLR\ts\rgT\x00OrNqV\n\bNgpnzs\nuoTQPUG\tUno\"Tvuvti\"QQZMML\bO\nnNLM\bgLrSNOGh\to\"n\aZhVONLpNgP\"NVrs", .UNION_SIZE=320},
        {.SUT="sQ\nGsG\aorQr\tps\x00oq\aqsLMHoh\"HgzsMQL\"\roP\agovNTps\x00\x00\x00TrghG\rvMNIog\x00P", .SUT_SIZE=62, .OTHER="ohMMV\n\buSQo\aMposs\alG\aTOPOzmrogv\rHuN\nmU\tI\tgh\t\"SLRLp\t\rmQ\tTnUZU\r\nqupSsL\riRVOpINnmR\x00lq\aMs\bntQTS\nuzQq\aRHRVH\n\nz\tQRR\aSo\x00\x00PSItggHzmzvv\n", .OTHER_SIZE=127, .UNION="sQ\nGsG\aorQr\tps\x00oq\aqsLMHoh\"HgzsMQL\"\roP\agovNTps\x00\x00\x00TrghG\rvMNIog\x00PohMMV\n\buSQo\aMposs\alG\aTOPOzmrogv\rHuN\nmU\tI\tgh\t\"SLRLp\t\rmQ\tTnUZU\r\nqupSsL\riRVOpINnmR\x00lq\aMs\bntQTS\nuzQq\aRHRVH\n\nz\tQRR\aSo\x00\x00PSItggHzmzvv\n", .UNION_SIZE=189},
        {.SUT="\"pLMNnoV\anU\nQ\anHqVLS\bhp\aNzlzg\rROUs", .SUT_SIZE=34, .OTHER="Qhg\blMsqqhQvOGpIMTr\x00QQqHg\aRoGH\aPvsl\x00giMLSU\x00tmINgz\bMptRLI\"piT\rG\a\rPHU\tvOPmStM\r\tUSOhRvL\niHOr\b\bGn\aQ\x00QomO\"zoV\x00\a\btUuI\nRlTzGqqoGNh\aRI\rUR\rniuIvPRVRgLIU\x00\rI\bQ\nNPhr\an\aTrqgS\rl\ti\"RIRP\ttrVV\"MRsO\"RnunVQ\aM\rhSzV\a\t\"nmSILHiR\x00iOGHh\nvvrV\bi\bHMiT\tNZ\aqHzvhuriRIPU", .OTHER_SIZE=239, .UNION="\"pLMNnoV\anU\nQ\anHqVLS\bhp\aNzlzg\rROUsQhg\blMsqqhQvOGpIMTr\x00QQqHg\aRoGH\aPvsl\x00giMLSU\x00tmINgz\bMptRLI\"piT\rG\a\rPHU\tvOPmStM\r\tUSOhRvL\niHOr\b\bGn\aQ\x00QomO\"zoV\x00\a\btUuI\nRlTzGqqoGNh\aRI\rUR\rniuIvPRVRgLIU\x00\rI\bQ\nNPhr\an\aTrqgS\rl\ti\"RIRP\ttrVV\"MRsO\"RnunVQ\aM\rhSzV\a\t\"nmSILHiR\x00iOGHh\nvvrV\bi\bHMiT\tNZ\aqHzvhuriRIPU", .UNION_SIZE=273},
        {.SUT="uZ\tR\rrIHViHorMNqTu\tU\tRVqhiLn\x00h\rr\nupnrRiPSgP\aqnTHlZu\nMTmOMN\thhluH\tlTumITnRmMrHH\apLtsQGIHg\x00\x00sHzRQNPL\bgppMnnVz\bMtqLGP\nuNlsIOSp\bZ\"gvU\rGZQRLrzmO\asTLSIOMZ\nzqMnUQS\tNh\n\rPMH\nzRiOVqVz\tNQTr\an\t\"hM", .SUT_SIZE=184, .OTHER="\tMuSvmn\rt\x00LrVt\"i\x00Ss\rVhPvpS\x00TrM\rzvOUUVnsIZOtMhQisGZs\ttNoq\rs\aMS\x00Vil\"\x00tLZZgiZ\x00tr\n\t\nzVvL\tSrinOVLQHLMQRU\nHSlz\"\rTSVV\"uGrRtPShusqrL\"uqm\x00\bNL\x00P\"I", .OTHER_SIZE=136, .UNION="uZ\tR\rrIHViHorMNqTu\tU\tRVqhiLn\x00h\rr\nupnrRiPSgP\aqnTHlZu\nMTmOMN\thhluH\tlTumITnRmMrHH\apLtsQGIHg\x00\x00sHzRQNPL\bgppMnnVz\bMtqLGP\nuNlsIOSp\bZ\"gvU\rGZQRLrzmO\asTLSIOMZ\nzqMnUQS\tNh\n\rPMH\nzRiOVqVz\tNQTr\an\t\"hM\tMuSvmn\rt\x00LrVt\"i\x00Ss\rVhPvpS\x00TrM\rzvOUUVnsIZOtMhQisGZs\ttNoq\rs\aMS\x00Vil\"\x00tLZZgiZ\x00tr\n\t\nzVvL\tSrinOVLQHLMQRU\nHSlz\"\rTSVV\"uGrRtPShusqrL\"uqm\x00\bNL\x00P\"I", .UNION_SIZE=320},
        {.SUT="\nvP\aTrVHuUiimnmgr\x00r\aUM\nVuzo\"GvqSVMzZi\x00i\thZV\aUONVQuPvhgQppl\bGprUqHVGgTZQi\x00LNs\tZRIvGsvQStpRHQVSRlRQORuPpoGgvZ\rnvhPhI\rOVg\"p\n\tH\t\rNutHSH\tLMzZvpnTmZ\rHmrQGnorH\bo\"m", .SUT_SIZE=156, .OTHER="P\ts\nSLHVVr\ttUiuzMHmNQ\atZZ\x00s\a\x00G\x00Hl\"\bIsNGqLh", .OTHER_SIZE=42, .UNION="\nvP\aTrVHuUiimnmgr\x00r\aUM\nVuzo\"GvqSVMzZi\x00i\thZV\aUONVQuPvhgQppl\bGprUqHVGgTZQi\x00LNs\tZRIvGsvQStpRHQVSRlRQORuPpoGgvZ\rnvhPhI\rOVg\"p\n\tH\t\rNutHSH\tLMzZvpnTmZ\rHmrQGnorH\bo\"mP\ts\nSLHVVr\ttUiuzMHmNQ\atZZ\x00s\a\x00G\x00Hl\"\bIsNGqLh", .UNION_SIZE=198},
};

const size_t BYTES_SEEDS_SIZE = sizeof(BYTES_SEEDS) / sizeof(BYTES_SEEDS[0]);

FeatureDefine(StringAppend) {
    (void) traits_context;

    kit_String sut;
    kit_String other;
    ImmutableOption option;

    for (size_t i = 0; i < BYTES_SEEDS_SIZE; i++) {
        const struct Seed SEED = BYTES_SEEDS[i];
        traits_assert(SEED.UNION_SIZE == SEED.SUT_SIZE + SEED.OTHER_SIZE);

        sut = I(kit_String_fromBytes(SEED.SUT, SEED.SUT_SIZE));
        assert_equal(kit_String_size(sut), SEED.SUT_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        other = I(kit_String_fromBytes(SEED.OTHER, SEED.OTHER_SIZE));
        assert_equal(kit_String_size(other), SEED.OTHER_SIZE);
        assert_greater_equal(kit_String_capacity(other), KIT_STRING_DEFAULT_CAPACITY);

        option = kit_String_append(&sut, other);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);
        assert_equal(kit_String_size(other), SEED.OTHER_SIZE);
        assert_greater_equal(kit_String_capacity(other), KIT_STRING_DEFAULT_CAPACITY);

        sut = I(option);
        assert_equal(0, memcmp(sut, SEED.UNION, SEED.UNION_SIZE));
        assert_equal(kit_String_size(sut), SEED.UNION_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);
        kit_String_delete(other);
    }

    for (size_t i = 0; i < LITERAL_SEEDS_SIZE; i++) {
        const struct Seed SEED = LITERAL_SEEDS[i];
        traits_assert(SEED.UNION_SIZE == SEED.SUT_SIZE + SEED.OTHER_SIZE);

        sut = I(kit_String_fromLiteral(SEED.SUT));
        assert_equal(kit_String_size(sut), SEED.SUT_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        other = I(kit_String_fromLiteral(SEED.OTHER));
        assert_equal(kit_String_size(other), SEED.OTHER_SIZE);
        assert_greater_equal(kit_String_capacity(other), KIT_STRING_DEFAULT_CAPACITY);

        option = kit_String_append(&sut, other);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);
        assert_equal(kit_String_size(other), SEED.OTHER_SIZE);
        assert_greater_equal(kit_String_capacity(other), KIT_STRING_DEFAULT_CAPACITY);

        sut = I(option);
        assert_string_equal(sut, SEED.UNION);
        assert_equal(kit_String_size(sut), SEED.UNION_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);
        kit_String_delete(other);
    }
}

FeatureDefine(StringAppendBytes) {
    (void) traits_context;

    kit_String sut;
    for (size_t i = 0; i < BYTES_SEEDS_SIZE; i++) {
        const struct Seed SEED = BYTES_SEEDS[i];
        traits_assert(SEED.UNION_SIZE == SEED.SUT_SIZE + SEED.OTHER_SIZE);

        sut = I(kit_String_fromBytes(SEED.SUT, SEED.SUT_SIZE));
        assert_equal(kit_String_size(sut), SEED.SUT_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_appendBytes(&sut, SEED.OTHER, SEED.OTHER_SIZE);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = I(option);
        assert_equal(0, memcmp(sut, SEED.UNION, SEED.UNION_SIZE));
        assert_equal(kit_String_size(sut), SEED.UNION_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);
    }
}

FeatureDefine(StringAppendFormat) {
    (void) traits_context;

    kit_String sut;
    for (size_t i = 0; i < LITERAL_SEEDS_SIZE; i++) {
        const struct Seed SEED = LITERAL_SEEDS[i];
        traits_assert(SEED.UNION_SIZE == SEED.SUT_SIZE + SEED.OTHER_SIZE);

        sut = I(kit_String_fromLiteral(SEED.SUT));
        assert_equal(kit_String_size(sut), SEED.SUT_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_appendFormat(&sut, "%s", SEED.OTHER);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = I(option);
        assert_string_equal(sut, SEED.UNION);
        assert_equal(kit_String_size(sut), SEED.UNION_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);
    }
}

FeatureDefine(StringAppendLiteral) {
    (void) traits_context;

    kit_String sut;
    for (size_t i = 0; i < LITERAL_SEEDS_SIZE; i++) {
        const struct Seed SEED = LITERAL_SEEDS[i];
        traits_assert(SEED.UNION_SIZE == SEED.SUT_SIZE + SEED.OTHER_SIZE);

        sut = I(kit_String_fromLiteral(SEED.SUT));
        assert_equal(kit_String_size(sut), SEED.SUT_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_appendLiteral(&sut, SEED.OTHER);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = I(option);
        assert_string_equal(sut, SEED.UNION);
        assert_equal(kit_String_size(sut), SEED.UNION_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);
    }
}

FeatureDefine(StringClear) {
    (void) traits_context;

    kit_String sut;
    ImmutableOption option;
    for (size_t i = 0; i < LITERAL_SEEDS_SIZE; i++) {
        const struct Seed SEED = LITERAL_SEEDS[i];
        traits_assert(SEED.UNION_SIZE == SEED.SUT_SIZE + SEED.OTHER_SIZE);

        sut = I(kit_String_fromLiteral(SEED.SUT));
        assert_equal(kit_String_size(sut), SEED.SUT_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        option = kit_String_clear(&sut);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = I(option);
        assert_string_equal(sut, "");
        assert_equal(kit_String_size(sut), 0);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);

        sut = I(kit_String_fromLiteral(SEED.OTHER));
        assert_equal(kit_String_size(sut), SEED.OTHER_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        option = kit_String_clear(&sut);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = I(option);
        assert_string_equal(sut, "");
        assert_equal(kit_String_size(sut), 0);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);

        sut = I(kit_String_fromLiteral(SEED.UNION));
        assert_equal(kit_String_size(sut), SEED.UNION_SIZE);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        option = kit_String_clear(&sut);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = I(option);
        assert_string_equal(sut, "");
        assert_equal(kit_String_size(sut), 0);
        assert_greater_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(sut);
    }
}
