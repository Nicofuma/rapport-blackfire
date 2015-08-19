# Insertion d'un chargeur de module personnalisé en tête (il sera toujours appelé en premier)
sys.meta_path.insert(0, ImportHookFinder())

# Lecture des hooks dans le fichier de configuration
for section in _config_object.sections():
  function = _config_object.get(section, 'function')
  (module, object_path) = function.split(':', 1)
  
  # Création du hook à partir d'une fonction de rappel
  hook = _function_trace_import_hook(object_path)
  
  # Enregistrement du hook
  register_import_hook(module, hook)
  
# -----------
# Fonction de rappel permettant de décorer une méthode
def _function_trace_import_hook(object_path, name):
  # Fonction appelée pour effectivement décorer une méthode.
  # target et le module contenant la méthode à décorer
  def _instrument(target):
    wraper = ... # création du décorateur
    
    # On remplace la fonction originale par le décorateur
    setattr(target, object_path, wrapper)

  return _instrument

# Chargeur de module personnalisé
class ImportHookFinder:
  # Méthode appelé pour charger un module
  def find_module(self, fullname, path=None):
    # Chargement du module
    # ...
    
    # Exécution des hooks
    for hook in _import_hooks.get(name):
        hook(module)
